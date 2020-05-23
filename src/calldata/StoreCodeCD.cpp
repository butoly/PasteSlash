#include "calldata/StoreCodeCD.h"

void StoreCodeCD::proceed(bool) {
    if (status == CREATE) {
        status = PROCESS;

        service->RequestStoreCode(&ctx, &gCode, &responder, cq, cq, this);
    } else if (status == PROCESS) {
        new StoreCodeCD(service, cq);

        Models::Code mCode = converter.CodeFromGRPC(gCode);

        ucase = std::make_unique<StoreCodeUsecase>(&mCode, gCode.user_id());
        int error = ucase->execute();

        switch (error) {
            case 0:
                break;
            case -1:
                finish(::grpc::Status(::grpc::DATA_LOSS, "data loss"));
                return;
            case -2:
                finish(::grpc::Status(::grpc::UNAVAILABLE, "unknown error"));
                return;
            default:
                break;
        }
        gHash.set_value(mCode.hash);

        finish(::grpc::Status::OK);
    } else {
        GPR_ASSERT(status == FINISH);
        delete this;
    }
}
