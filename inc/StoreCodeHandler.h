#ifndef PROJECT_STORECODEHANDLER_H
#define PROJECT_STORECODEHANDLER_H

#include <iostream>
#include <vector>

#include "Application.h"
#include "AbstractHandler.h"


class StoreCodeHandler : public AbstractHanlder {
private:
    std::vector<int> request;
    int* response;
public:
    StoreCodeHandler(std::vector<int> req, int* res) : request(req), response(res) {};
    ~StoreCodeHandler() = default;

    void execute() override;
};

#endif //PROJECT_STORECODEHANDLER_H
