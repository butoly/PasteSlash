#ifndef PROJECT_AUTHUSERHANDLER_H
#define PROJECT_AUTHUSERHANDLER_H

#include <iostream>
#include <vector>

#include "AbstractUsecase.h"


class AuthUserUsecase : public AbstractUsecase {
private:
    const ::Models::User& user;
    Models::Token token;

public:
    explicit AuthUserUsecase(const ::Models::User& u, Models::Token& t) : user(u), token(t) {};
    ~AuthUserUsecase() = default;

    int execute() override;
};

#endif //PROJECT_AUTHUSERHANDLER_H
