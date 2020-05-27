#include "server/calldata/CheckTokenCD.h"

void CheckTokenCD::proceed(bool) {
    if (status == CREATE) {
        status = PROCESS;

        service->RequestCheckToken(&ctx, &gToken, &responder, cq, cq, this);
    } else if (status == PROCESS) {
        new CheckTokenCD(service, cq);

        std::string token = gToken.token();

        //проверка есть ли такой в бд и не истек ли срок
        int user_id = UserDBManager::isTokenExist(token);
        if (user_id == 0) {
            finish(::grpc::Status(::grpc::NOT_FOUND, "token not found or expired"));
            return;
        }

        aToken.set_token(token);
        aToken.set_user_id(user_id);
        finish(::grpc::Status::OK);

    } else {
        GPR_ASSERT(status == FINISH);
        delete this;
    }
}

