#ifndef PROJECT_AUTHUSERHANDLER_H
#define PROJECT_AUTHUSERHANDLER_H

#include <iostream>
#include <vector>

#include "AbstractUsecase.h"


class AuthUserUsecase : public AbstractUsecase {
private:
    std::vector<int> request;
    int* response;
public:
    AuthUserUsecase(std::vector<int> req, int* res) : request(req), response(res) {};
    ~AuthUserUsecase() = default;

    void execute() override;
};

#endif //PROJECT_AUTHUSERHANDLER_H
