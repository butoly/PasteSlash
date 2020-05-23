#ifndef PROJECT_GETCODEUSECASE_H
#define PROJECT_GETCODEUSECASE_H

#include <iostream>
#include <vector>

#include "AbstractUsecase.h"


class GetCodeUsecase : public AbstractUsecase {
private:
    std::string hash;
    Models::Code code;

public:
    GetCodeUsecase(std::string& h, Models::Code& c) : hash(h), code(c) {};
    ~GetCodeUsecase() = default;

    int execute() override;
};

#endif //PROJECT_GETCODEUSECASE_H
