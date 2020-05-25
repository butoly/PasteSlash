#ifndef PROJECT_GETCODECD_H
#define PROJECT_GETCODECD_H

#include "BaseCallData.h"
#include "Models.h"
#include "usecases/GetCodeUsecase.h"

class GetCodeCD : BaseCallData {
private:
    ::grpc::ServerAsyncResponseWriter<Code> responder;
    Code gCode;
    Hash gHash;
    Models::Code mCode;

    void finish(const ::grpc::Status& s) {
        status = FINISH;

        responder.Finish(gCode, s, this);
    }

public:
    GetCodeCD(::AppLayer::AsyncService* s, ::grpc::ServerCompletionQueue* q) : BaseCallData(s, q), responder(&ctx) {
            proceed();
    }

    void proceed(bool = true) override;
};


#endif //PROJECT_GETCODECD_H
