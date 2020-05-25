#ifndef PROJECT_DELETECODEUSECASE_H
#define PROJECT_DELETECODEUSECASE_H

#include <iostream>
#include <vector>

#include "AbstractUsecase.h"


class DeleteCodeUsecase : public AbstractUsecase {
private:
    std::string hash;
public:
    DeleteCodeUsecase(std::string& h) : hash(h) {};
    ~DeleteCodeUsecase() = default;

    int execute() override;
};

#endif //PROJECT_DELETECODEUSECASE_H
