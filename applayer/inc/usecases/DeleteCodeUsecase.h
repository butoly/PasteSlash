#ifndef PROJECT_DELETECODEUSECASE_H
#define PROJECT_DELETECODEUSECASE_H

#include <iostream>
#include <vector>

#include "AbstractUsecase.h"


class DeleteCodeUsecase : public AbstractUsecase {
private:
    std::string hash;
    int user_id;
public:
    DeleteCodeUsecase(std::string& h, int uid) : hash(h), user_id(uid) {};
    ~DeleteCodeUsecase() = default;

    int execute() override;
};

#endif //PROJECT_DELETECODEUSECASE_H
