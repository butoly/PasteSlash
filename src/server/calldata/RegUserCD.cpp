#include "server/calldata/RegUserCD.h"

void RegUserCD::proceed(bool) {
    if (status == CREATE) {
        status = PROCESS;

        service->RequestRegUser(&ctx, &gUser, &responder, cq, cq, this);
    } else if (status == PROCESS) {
        new RegUserCD(service, cq);

        Models::User mUser = converter.UserFromGRPC(gUser);

        Models::Token mToken;

        ucase = std::make_unique<RegUserUsecase>(mUser,&mToken);

        int error = ucase->execute();
        ::grpc::Status status;

        switch (error){
            case 0:
                break;
            case -1:
                finish(::grpc::Status(::grpc::ALREADY_EXISTS, "nickname already exists"));
                return;
            case - 2:
                finish(::grpc::Status(::grpc::ALREADY_EXISTS, "email already exists"));
                return;
            default:
                break;
        }

        gToken = converter.TokenFromModel(mToken);

        finish(::grpc::Status::OK);
    } else {
        GPR_ASSERT(status == FINISH);
        delete this;
    }

}
