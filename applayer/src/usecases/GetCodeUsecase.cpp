#include "usecases/GetCodeUsecase.h"

int GetCodeUsecase::execute() {

    bool isFound = true;

    auto recCode = PasteDBManager::getPaste(hash);

    std::cout << recCode << std::endl;


//    Models::Code c(recCode["name"], recCode["body"]);

    if (!isFound) {
        return -1;
    }

    bool isOk;
    if (!isOk){
        return -2;
    }
    //достаем из бд код

    return 0;
}