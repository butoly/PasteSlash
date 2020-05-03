#ifndef PROJECT_REQUESTHANDLER_H
#define PROJECT_REQUESTHANDLER_H

#include "Parser.h"
#include "usecases/AbstractUsecase.h"
#include "usecases/StoreCodeUsecase.h"
#include "usecases/RegUserUsecase.h"
#include "usecases/GetCodeUsecase.h"
#include "usecases/DeleteCodeUsecase.h"
#include "usecases/AuthUserUsecase.h"

class RequestHandler {
    Parser parser;
    std::unique_ptr<AbstractUsecase> ucase;

public:
    RequestHandler() : ucase(nullptr) {};
    void handle(std::string& data);
};


#endif //PROJECT_REQUESTHANDLER_H
