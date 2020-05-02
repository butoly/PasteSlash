#ifndef PROJECT_REQUESTMANAGER_H
#define PROJECT_REQUESTMANAGER_H

#include "Parser.h"
#include "usecases/AbstractHandler.h"

class RequestManager {
    Parser parser;
    AbstractHanlder* handler;

public:
    explicit RequestManager() {}

    void handle(std::string data);
};


#endif //PROJECT_REQUESTMANAGER_H
