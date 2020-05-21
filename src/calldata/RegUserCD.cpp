#include "calldata/RegUserCD.h"

void RegUserCD::proceed(bool) {
    if (status == CREATE) {
        status = PROCESS;

        service->RequestRegUser(&ctx, &gUser, &responder, cq, cq, this);
    } else if (status == PROCESS) {
        new RegUserCD(service, cq);

        Models::User mUser = converter.UserFromGRPC(gUser);

        //заглушка для проверки, есть ли такой ник уже в бд
        bool hasN;
        if (hasN) {
            finish(::grpc::Status(::grpc::ALREADY_EXISTS, "nickname already exists"));
            return;
        }
        //заглушка для проверки, есть ли такой mail уже в бд
        bool hasE;
        if (hasE) {
            finish(::grpc::Status(::grpc::ALREADY_EXISTS, "email already exists"));
            return;
        }

//        ucase = std::make_unique<RegUserUsecase>(user);
//        ucase->execute();

        //генерируем access токен
        std::string tokenValue = "token";
        Models::Token token(tokenValue);
        gToken = converter.TokenFromModel(token);

        finish(::grpc::Status::OK);
    } else {
        GPR_ASSERT(status == FINISH);
        delete this;
    }

}
