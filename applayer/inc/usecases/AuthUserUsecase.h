#ifndef PROJECT_AUTHUSERHANDLER_H
#define PROJECT_AUTHUSERHANDLER_H

#include <iostream>
#include <vector>
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.
#include <boost/lexical_cast.hpp>

#include "AbstractUsecase.h"


class AuthUserUsecase : public AbstractUsecase {
private:
    const ::Models::User& user;
    Models::Token* token;

public:
    explicit AuthUserUsecase(const ::Models::User& u, Models::Token* t) : user(u), token(t) {};
    ~AuthUserUsecase() = default;

    int execute() override;
};

#endif //PROJECT_AUTHUSERHANDLER_H
