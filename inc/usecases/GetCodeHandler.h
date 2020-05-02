#ifndef PROJECT_GETCODEHANDLER_H
#define PROJECT_GETCODEHANDLER_H

#include <iostream>
#include <vector>

#include "Application.h"
#include "AbstractHandler.h"


class GetCodeHandler : public AbstractHanlder {
private:
    std::vector<int> request;
    int* response;
public:
    GetCodeHandler(std::vector<int> req, int* res) : request(req), response(res) {};
    ~GetCodeHandler() = default;

    void execute() override;
};

#endif //PROJECT_GETCODEHANDLER_H
