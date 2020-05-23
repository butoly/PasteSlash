#include "calldata/GetCodeCD.h"

void GetCodeCD::proceed(bool) {
    if (status == CREATE) {
        status = PROCESS;

        service->RequestGetCode(&ctx, &gHash, &responder, cq, cq, this);
    } else if (status == PROCESS) {
        new GetCodeCD(service, cq);

        std::string mHash = converter.HashFromGRPC(gHash);

        ucase = std::make_unique<GetCodeUsecase>(mCode, mHash);
        int error = ucase->execute();

        switch (error){
            case 0:
                break;
            case -1:
                finish(::grpc::Status(::grpc::NOT_FOUND, "code not found"));
                return;
            default:
                break;
        }

        gCode = converter.CodeFromModels(mCode);

        finish(::grpc::Status::OK);
    } else {
        GPR_ASSERT(status == FINISH);
        delete this;
    }


}
