#include "server/calldata/GetAllHashesCD.h"

void GetAllHashesCD::proceed(bool) {
    if (status == CREATE) {
        status = PROCESS;

        service->RequestGetAllHashes(&ctx, &gUser, &responder, cq, cq, this);
    } else if (status == PROCESS) {
        new GetAllHashesCD(service, cq);

        Models::User mUser = converter.UserFromGRPC(gUser);

        std::vector<std::string>hashes;

        ucase = std::make_unique<GetAllHashesUsecase>(mUser, &hashes);
        int error = ucase->execute();

        switch (error){
            case 0:
                break;
            case -1:
                finish(::grpc::Status(::grpc::NOT_FOUND, "hashes not found"));
                return;
            default:
                break;
        }

        for (std::string h: hashes) {
            gHashes.add_hashes()->set_value(h);
        }

        finish(::grpc::Status::OK);
    } else {
        GPR_ASSERT(status == FINISH);
        delete this;
    }
}
