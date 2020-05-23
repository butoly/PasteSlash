#include "calldata/AuthUserCD.h"

void AuthUserCD::proceed(bool) {
    if (status == CREATE) {
        status = PROCESS;

        service->RequestAuthUser(&ctx, &gUser, &responder, cq, cq, this);
    } else if (status == PROCESS) {
        new AuthUserCD(service, cq);

        Models::User mUser = converter.UserFromGRPC(gUser);

        //заглушка для проверки, есть ли такой ник вообще в бд
        bool hasN;
        if (!hasN) {
            finish(::grpc::Status(::grpc::NOT_FOUND, "user not found"));
            return;
        }

        Models::Token mToken;

        ucase = std::make_unique<AuthUserUsecase>(mUser, mToken);

        int error = ucase->execute();
        ::grpc::Status status;

        switch (error){
            case 0:
                break;
            case -1:
                finish(::grpc::Status(::grpc::NOT_FOUND, "user not found"));
                return;
            case - 2:
                finish(::grpc::Status(::grpc::INVALID_ARGUMENT, "wrong login or password"));
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
