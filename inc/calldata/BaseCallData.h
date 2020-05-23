#ifndef PROJECT_BASECALLDATA_H
#define PROJECT_BASECALLDATA_H


#include "gen/AppLayer.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include "GRPCConverter.h"
#include "usecases/AbstractUsecase.h"

class BaseCallData {
protected:
    ::AppLayer::AsyncService* service;
    ::grpc::ServerCompletionQueue* cq;
    ::grpc::ServerContext ctx;
    std::unique_ptr<AbstractUsecase> ucase;

    GRPCConverter converter;

    enum CallStatus {CREATE, PROCESS, FINISH};

    CallStatus status;

public:
    BaseCallData(::AppLayer::AsyncService* s, ::grpc::ServerCompletionQueue* q)
    : service(s),
      cq(q),
      status(CREATE)
    {}

    virtual ~BaseCallData() {}

    virtual void proceed(bool = true) = 0;
};


#endif //PROJECT_BASECALLDATA_H
