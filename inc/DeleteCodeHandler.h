#ifndef PROJECT_DELETECODEHANDLER_H
#define PROJECT_DELETECODEHANDLER_H

#include <iostream>
#include <vector>

#include "Application.h"
#include "AbstractHandler.h"


class DeleteCodeHandler : public AbstractHanlder {
private:
    std::vector<int> request;
    int* response;
public:
    DeleteCodeHandler(std::vector<int> req, int* res) : request(req), response(res) {};
    ~DeleteCodeHandler() = default;

    void execute() override;
};

#endif //PROJECT_DELETECODEHANDLER_H
