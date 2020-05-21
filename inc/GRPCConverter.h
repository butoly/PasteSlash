#ifndef PROJECT_GRPCCONVERTER_H
#define PROJECT_GRPCCONVERTER_H

#include "Models.h"
#include "gen/AppLayer.pb.h"

class GRPCConverter {
public:
    GRPCConverter() = default;

    ~GRPCConverter() = default;

    Models::User UserFromGRPC(const ::User& gUser);

    Token TokenFromModel(const Models::Token& token);
};



#endif //PROJECT_GRPCCONVERTER_H
