#include "usecases/GetCodeUsecase.h"

int GetCodeUsecase::execute() {

    bool isFound = PasteDBManager::checkHash(hash);

    if (!isFound) {
        return -1;
    }

    auto recCode = PasteDBManager::getPaste(hash);

    std::cout << recCode << std::endl;

    std::unordered_map<std::string, std::string>rc = *recCode;

    code->name = rc["title"];
    code->body = rc["text"];
    code->hash = rc["hash"];

    if (code->body.empty()){
        return -2;
    }

    return 0;
}
