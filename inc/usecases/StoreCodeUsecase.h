#ifndef PROJECT_STORECODEUSECASE_H
#define PROJECT_STORECODEUSECASE_H

#include <iostream>
#include <vector>

#include "AbstractUsecase.h"


class StoreCodeUsecase : public AbstractUsecase {
private:
    std::vector<int> request;
    int* response;
public:
    StoreCodeUsecase(std::vector<int> req, int* res) : request(req), response(res) {};
    ~StoreCodeUsecase() = default;

    void execute() override;
};

#endif //PROJECT_STORECODEUSECASE_H
