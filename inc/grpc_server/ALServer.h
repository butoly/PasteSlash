#ifndef PROJECT_ALSERVER_H
#define PROJECT_ALSERVER_H


#include "gen/AppLayer.grpc.pb.h"
#include "gen/AppLayer.pb.h"
#include "Models.h"
#include "GRPCConverter.h"

#include <grpc++/server_builder.h>
#include <grpc/grpc.h>


class ALServer final: public AppLayer::Service {
public:
    ::grpc::Status RegUser(::grpc::ServerContext* context, const ::User* request, ::Token* response);
    ::grpc::Status AuthUser(::grpc::ServerContext* context, const ::User* request, ::Token* response);

private:
    GRPCConverter converter;
};





#endif //PROJECT_ALSERVER_H
