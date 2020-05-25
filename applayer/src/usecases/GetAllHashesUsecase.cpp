#include "usecases/GetAllHashesUsecase.h"

int GetAllHashesUsecase::execute() {

    bool userIsFound = true;
    if (!userIsFound) {
        return -1;
    }

    bool hashesIsFound = true;
    if (!hashesIsFound){
        return -2;
    }
    //достаем из бд код
    std::string h1 = "hash1";
    hashes->push_back(h1);

    std::string h2 = "hash2";
    hashes->push_back(h2);

    return 0;
}
