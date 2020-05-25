#ifndef PROJECT_GETALLHASHESCD_H
#define PROJECT_GETALLHASHESCD_H

#include "BaseCallData.h"
#include "Models.h"
#include "usecases/GetAllHashesUsecase.h"

class GetAllHashesCD : public BaseCallData{
private:
    ::grpc::ServerAsyncResponseWriter<Hashes> responder;
    Hashes gHashes;
    User gUser;

    void finish(const ::grpc::Status& s) {
        status = FINISH;

        responder.Finish(gHashes, s, this);
    }

public:
    GetAllHashesCD(::AppLayer::AsyncService* s, ::grpc::ServerCompletionQueue* q) : BaseCallData(s, q), responder(&ctx) {
            proceed();
    }

    void proceed(bool = true) override;
};


#endif //PROJECT_GETALLHASHESCD_H
