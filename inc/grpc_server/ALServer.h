#ifndef PROJECT_ALSERVER_H
#define PROJECT_ALSERVER_H

#include "gen/AppLayer.grpc.pb.h"
#include "gen/AppLayer.pb.h"
#include "Models.h"
#include "GRPCConverter.h"
#include "calldata/RegUserCD.h"

#include <memory>
#include <grpc++/server_builder.h>
#include <grpcpp/grpcpp.h>


//class ALServer final: public AppLayer::Service {
//public:
//    ::grpc::Status RegUser(::grpc::ServerContext* context, const ::User* request, ::Token* response);
//    ::grpc::Status AuthUser(::grpc::ServerContext* context, const ::User* request, ::Token* response);
//
//private:
//    GRPCConverter converter;
//};

class ALServer {
private:
    std::unique_ptr<::grpc::ServerCompletionQueue> cq;
    ::AppLayer::AsyncService service;
    std::unique_ptr<::grpc::Server> server;
    ::grpc::ServerBuilder builder;

public:
    ALServer(const std::string& ip, const std::string& port) {
        std::string address = ip + ":" + port;
        builder.AddListeningPort(address, ::grpc::InsecureServerCredentials());
    }
    ~ALServer() {
        server->Shutdown();
        cq->Shutdown();
    }

    void run() {
        builder.RegisterService(&service);
        cq = builder.AddCompletionQueue();
        server = builder.BuildAndStart();

        void* tag;
        bool ok;

        new RegUserCD(&service, cq.get());
        while (true) {
            GPR_ASSERT(cq->Next(&tag, &ok));
            BaseCallData* callData = static_cast<BaseCallData*>(tag);
            callData->proceed(ok);
        }
    }
};



#endif //PROJECT_ALSERVER_H
