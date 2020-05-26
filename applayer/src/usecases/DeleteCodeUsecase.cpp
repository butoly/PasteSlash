#include "usecases/DeleteCodeUsecase.h"

int DeleteCodeUsecase::execute() {

    bool isFound;
    if (!isFound) {
        return -1;
    }

    PasteDBManager::deleteOverduePastes();

    bool Delete;
    if (!Delete) {
        return -2;
    }

    return 0;
}