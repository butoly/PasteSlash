#include "GRPCConverter.h"

Models::User* GRPCConverter::UserFromGRPC(const ::User* gUser) {
    return new Models::User(std::string(gUser->nickname()),
                            std::string(gUser->email()),
                            std::string(gUser->password()));
}
