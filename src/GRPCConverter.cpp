#include "GRPCConverter.h"

Models::User GRPCConverter::UserFromGRPC(const ::User& gUser) {
    return Models::User(std::string(gUser.nickname()),
                            std::string(gUser.email()),
                            std::string(gUser.password()));
}

Token GRPCConverter::TokenFromModel(const Models::Token& token) {
    Token t;
    t.set_token(token.value);
    return t;
}
