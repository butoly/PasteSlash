#ifndef PROJECT_CHECKTOKENCD_H
#define PROJECT_CHECKTOKENCD_H

#include "BaseCallData.h"

class CheckTokenCD : public BaseCallData {
private:
    ::grpc::ServerAsyncResponseWriter<AccessToken> responder;
    AccessToken aToken;
    Token gToken;

    void finish(const ::grpc::Status& s) {
        status = FINISH;

        responder.Finish(aToken, s, this);
    }

public:
    CheckTokenCD(::AppLayer::AsyncService* s, ::grpc::ServerCompletionQueue* q) : BaseCallData(s, q), responder(&ctx) {
            proceed();
    }

    void proceed(bool = true) override;
};


#endif //PROJECT_CHECKTOKENCD_H
