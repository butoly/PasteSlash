#ifndef PROJECT_GRPCCONVERTER_H
#define PROJECT_GRPCCONVERTER_H

#include "Models.h"
#include "gen/AppLayer.pb.h"

class GRPCConverter {
public:
    GRPCConverter() = default;

    ~GRPCConverter() = default;

    Models::User UserFromGRPC(const ::User& gUser);

    Models::Code CodeFromGRPC(const ::Code& gCode);

    std::string HashFromGRPC(const ::Hash& gHash);

    Token TokenFromModel(const Models::Token& token);

    Code CodeFromModels(const Models::Code& code);

};



#endif //PROJECT_GRPCCONVERTER_H
