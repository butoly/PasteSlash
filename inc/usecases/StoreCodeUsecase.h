#ifndef PROJECT_STORECODEUSECASE_H
#define PROJECT_STORECODEUSECASE_H

#include <iostream>
#include <vector>

#include "AbstractUsecase.h"


class StoreCodeUsecase : public AbstractUsecase {
private:
    ::Models::Code& code;
    int user_id;

public:
    explicit StoreCodeUsecase(::Models::Code& c, int id) : code(c), user_id(id) {};
    ~StoreCodeUsecase() = default;

    int execute() override;
};

#endif //PROJECT_STORECODEUSECASE_H
