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

//        ucase = std::make_unique<AuthUserUsecase>(user);
//
//        ucase->execute();

        //достаем/генерируем из бд токен
        std::string tokenValue = "token";
        Models::Token token(tokenValue);
        gToken = converter.TokenFromModel(token);

        finish(::grpc::Status::OK);
    } else {
        GPR_ASSERT(status == FINISH);
        delete this;
    }
}
