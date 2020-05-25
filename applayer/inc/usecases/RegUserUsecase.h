#ifndef PROJECT_REGUSERUSECASE_H
#define PROJECT_REGUSERUSECASE_H

#include <iostream>
#include <vector>
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.
#include <boost/lexical_cast.hpp>

#include "AbstractUsecase.h"
#include "Models.h"


class RegUserUsecase : public AbstractUsecase {
private:
    const ::Models::User& user;
    Models::Token* token;

public:
    explicit RegUserUsecase(const ::Models::User& u, Models::Token* t) : user(u), token(t) {};
    ~RegUserUsecase() = default;

    int execute() override;
};

#endif //PROJECT_REGUSERUSECASE_H
