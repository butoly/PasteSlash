#ifndef PROJECT_REGUSERCD_H
#define PROJECT_REGUSERCD_H

#include "BaseCallData.h"
#include "Models.h"


class RegUserCD : public BaseCallData {
private:
    ::grpc::ServerAsyncResponseWriter<Token> responder;
    User gUser;
    Token gToken;

    void finish(const ::grpc::Status& s) {
        status = FINISH;

        responder.Finish(gToken, s, this);
    }

public:
    RegUserCD(::AppLayer::AsyncService* s, ::grpc::ServerCompletionQueue* q) : BaseCallData(s, q), responder(&ctx) {}

    void proceed(bool = true) override;
};


#endif //PROJECT_REGUSERCD_H
