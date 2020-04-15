#ifndef PROJECT_REQUESTMANAGER_H
#define PROJECT_REQUESTMANAGER_H

#include "Parser.h"
#include "AbstractHandler.h"

template <typename Sender>
class RequestManager {
    Parser parser;
    AbstractHanlder* handler;
    Sender sender;

public:
    explicit RequestManager(Sender&& s) : sender(s) {}

    void handle(std::string data);
};


#endif //PROJECT_REQUESTMANAGER_H
