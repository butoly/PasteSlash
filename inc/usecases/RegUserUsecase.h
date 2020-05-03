#ifndef PROJECT_REGUSERUSECASE_H
#define PROJECT_REGUSERUSECASE_H

#include <iostream>
#include <vector>

#include "AbstractUsecase.h"


class RegUserUsecase : public AbstractUsecase {
private:
    std::vector<int> request;
    int* response;
public:
    RegUserUsecase(std::vector<int> req, int* res) : request(req), response(res) {};
    ~RegUserUsecase() = default;

    void execute() override;
};

#endif //PROJECT_REGUSERUSECASE_H
