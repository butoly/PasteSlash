#ifndef PROJECT_AUTHUSERHANDLER_H
#define PROJECT_AUTHUSERHANDLER_H

#include <iostream>
#include <vector>

#include "Application.h"
#include "AbstractHandler.h"


class AuthUserHandler : public AbstractHanlder {
private:
    std::vector<int> request;
    int* response;
public:
    AuthUserHandler(std::vector<int> req, int* res) : request(req), response(res) {};
    ~AuthUserHandler() = default;

    void execute() override;
};

#endif //PROJECT_AUTHUSERHANDLER_H
