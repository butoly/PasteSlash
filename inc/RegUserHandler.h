#ifndef PROJECT_REGUSERHANDLER_H
#define PROJECT_REGUSERHANDLER_H

#include <iostream>
#include <vector>

#include "Application.h"
#include "AbstractHandler.h"


class RegUserHandler : public AbstractHanlder {
private:
    std::vector<int> request;
    int* response;
public:
    RegUserHandler(std::vector<int> req, int* res) : request(req), response(res) {};
    ~RegUserHandler() = default;

    void execute() override;
};

#endif //PROJECT_REGUSERHANDLER_H
