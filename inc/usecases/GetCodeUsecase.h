#ifndef PROJECT_GETCODEUSECASE_H
#define PROJECT_GETCODEUSECASE_H

#include <iostream>
#include <vector>

#include "AbstractUsecase.h"


class GetCodeUsecase : public AbstractUsecase {
private:
    std::vector<int> request;
    int* response;
public:
    GetCodeUsecase(std::vector<int> req, int* res) : request(req), response(res) {};
    ~GetCodeUsecase() = default;

    void execute() override;
};

#endif //PROJECT_GETCODEUSECASE_H
