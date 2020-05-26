#include "usecases/DeleteCodeUsecase.h"

int DeleteCodeUsecase::execute() {

    if (!PasteDBManager::checkHash(hash)) {
        return -1;
    }

    PasteDBManager::deletePaste(hash);

    if (PasteDBManager::checkHash(hash)) {
        return -2;
    }

    return 0;
}