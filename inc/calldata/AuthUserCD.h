#ifndef PROJECT_AUTHUSERCD_H
#define PROJECT_AUTHUSERCD_H

#include "BaseCallData.h"
#include "Models.h"

class AuthUserCD : public BaseCallData {
private:
    ::grpc::ServerAsyncResponseWriter<Token> responder;
    User gUser;
    Token gToken;

    void finish(const ::grpc::Status& s) {
        status = FINISH;

        responder.Finish(gToken, s, this);
    }

public:
    AuthUserCD(::AppLayer::AsyncService* s, ::grpc::ServerCompletionQueue* q) : BaseCallData(s, q), responder(&ctx) {
            proceed();
    }

    void proceed(bool = true) override;
};


#endif //PROJECT_AUTHUSERCD_H
