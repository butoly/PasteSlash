#ifndef PROJECT_STORECODEUSECASE_H
#define PROJECT_STORECODEUSECASE_H

#include <iostream>
#include <vector>

#include "AbstractUsecase.h"


class StoreCodeUsecase : public AbstractUsecase {
private:
    ::Models::Code& code;

public:
    explicit StoreCodeUsecase(::Models::Code& c) : code(c) {};
    ~StoreCodeUsecase() = default;

    void execute() override;
};

#endif //PROJECT_STORECODEUSECASE_H
