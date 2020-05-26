#include "usecases/GetAllHashesUsecase.h"

int GetAllHashesUsecase::execute() {


    std::vector<std::string> hs = PasteDBManager::getHashList(user.nickname);

    for (const auto & h : hs){
        hashes->push_back(h);
    }

    return 0;
}
