#include "server/calldata/DeleteCodeCD.h"

void DeleteCodeCD::proceed(bool) {
    if (status == CREATE) {
        status = PROCESS;

        service->RequestDeleteCode(&ctx, &gHash, &responder, cq, cq, this);
    } else if (status == PROCESS) {
        new DeleteCodeCD(service, cq);

        std::string mHash = converter.HashFromGRPC(gHash);
        int user_id = gHash.user_id();

        ucase = std::make_unique<DeleteCodeUsecase>(mHash, user_id);
        int error = ucase->execute();

        switch (error){
            case 0:
                msg.set_message("code deleted");
                break;
            case -1:
                finish(::grpc::Status(::grpc::NOT_FOUND, "code not found"));
                return;
            case -2:
                finish(::grpc::Status(::grpc::UNKNOWN, "unknown error"));
                return;
            case -3:
                finish(::grpc::Status(::grpc::UNAVAILABLE, "no access"));
                return;
            default:
                break;
        }

        finish(::grpc::Status::OK);
    } else {
        GPR_ASSERT(status == FINISH);
        delete this;
    }


}
