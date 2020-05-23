#ifndef PROJECT_DELETECODECD_H
#define PROJECT_DELETECODECD_H

#include "BaseCallData.h"
#include "usecases/DeleteCodeUsecase.h"
#include "Models.h"

class DeleteCodeCD : public BaseCallData {
private:
    ::grpc::ServerAsyncResponseWriter<Error> responder;
    Error msg;
    Hash gHash;

    void finish(const ::grpc::Status& s) {
        status = FINISH;

        responder.Finish(msg, s, this);
    }

public:
    DeleteCodeCD(::AppLayer::AsyncService* s, ::grpc::ServerCompletionQueue* q) : BaseCallData(s, q), responder(&ctx) {
            proceed();
    }

    void proceed(bool = true) override;
};


#endif //PROJECT_DELETECODECD_H
