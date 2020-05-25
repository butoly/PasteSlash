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

Models::Code GRPCConverter::CodeFromGRPC(const ::Code& gCode) {
    return Models::Code(std::string(gCode.name()), std::string(gCode.text()));
}

Code GRPCConverter::CodeFromModels(const Models::Code& code) {
    Code c;
    c.set_name(code.name);
    c.set_text(code.body);

    return c;
}

std::string GRPCConverter::HashFromGRPC(const ::Hash& gHash) {
    return gHash.value();
}
