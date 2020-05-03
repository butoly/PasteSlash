#ifndef PROJECT_REGUSERUSECASE_H
#define PROJECT_REGUSERUSECASE_H

#include <iostream>
#include <vector>

#include "AbstractUsecase.h"
#include "Models.h"


class RegUserUsecase : public AbstractUsecase {
private:
    const User& user;

public:
    explicit RegUserUsecase(const User& u) : user(u) {};
    ~RegUserUsecase() = default;

    void execute() override;
};

#endif //PROJECT_REGUSERUSECASE_H
