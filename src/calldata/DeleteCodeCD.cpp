#include "calldata/DeleteCodeCD.h"

void DeleteCodeCD::proceed(bool) {
    if (status == CREATE) {
        status = PROCESS;

        service->RequestDeleteCode(&ctx, &gHash, &responder, cq, cq, this);
    } else if (status == PROCESS) {
        new DeleteCodeCD(service, cq);

        std::string mHash = converter.HashFromGRPC(gHash);

        ucase = std::make_unique<DeleteCodeUsecase>(mHash);
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
            default:
                break;
        }

        finish(::grpc::Status::OK);
    } else {
        GPR_ASSERT(status == FINISH);
        delete this;
    }


}
