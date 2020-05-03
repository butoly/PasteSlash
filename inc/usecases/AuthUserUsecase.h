#ifndef PROJECT_AUTHUSERHANDLER_H
#define PROJECT_AUTHUSERHANDLER_H

#include <iostream>
#include <vector>

#include "AbstractUsecase.h"


class AuthUserUsecase : public AbstractUsecase {
private:
    const User& user;

public:
    explicit AuthUserUsecase(const User& u) : user(u) {};
    ~AuthUserUsecase() = default;

    void execute() override;
};

#endif //PROJECT_AUTHUSERHANDLER_H
