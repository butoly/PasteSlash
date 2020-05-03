#ifndef PROJECT_DELETECODEUSECASE_H
#define PROJECT_DELETECODEUSECASE_H

#include <iostream>
#include <vector>

#include "AbstractUsecase.h"


class DeleteCodeUsecase : public AbstractUsecase {
private:
    std::vector<int> request;
    int* response;
public:
    DeleteCodeUsecase(std::vector<int> req, int* res) : request(req), response(res) {};
    ~DeleteCodeUsecase() = default;

    void execute() override;
};

#endif //PROJECT_DELETECODEUSECASE_H
