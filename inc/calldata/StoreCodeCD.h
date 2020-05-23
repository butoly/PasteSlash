#ifndef PROJECT_STORECODECD_H
#define PROJECT_STORECODECD_H

#include "BaseCallData.h"
#include "usecases/StoreCodeUsecase.h"
#include "Models.h"

class StoreCodeCD : public BaseCallData {
private:
    ::grpc::ServerAsyncResponseWriter<Hash> responder;
    Code gCode;
    Hash gHash;

    void finish(const ::grpc::Status& s) {
        status = FINISH;

        responder.Finish(gHash, s, this);
    }

public:
    StoreCodeCD(::AppLayer::AsyncService* s, ::grpc::ServerCompletionQueue* q) : BaseCallData(s, q), responder(&ctx) {
        proceed();
    }

    void proceed(bool = true) override;
};


#endif //PROJECT_STORECODECD_H
