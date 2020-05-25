#ifndef PROJECT_ALSERVER_H
#define PROJECT_ALSERVER_H

#include "gen/AppLayer.grpc.pb.h"
#include "gen/AppLayer.pb.h"

#include "Models.h"
#include "converter/GRPCConverter.h"

#include "calldata/calldata.h"

#include <memory>
#include <grpc++/server_builder.h>
#include <grpcpp/grpcpp.h>

class ALServer {
private:
    std::unique_ptr<::grpc::ServerCompletionQueue> cq;
    ::AppLayer::AsyncService service;
    std::unique_ptr<::grpc::Server> server;
    ::grpc::ServerBuilder builder;

public:
    ALServer(const std::string& ip, const std::string& port);
    ~ALServer();

    void run();
};



#endif //PROJECT_ALSERVER_H
