#include "usecases/DeleteCodeUsecase.h"

int DeleteCodeUsecase::execute() {

    if (!PasteDBManager::checkHash(hash)) {
        return -1;
    }

    int id_cUser = PasteDBManager::getPasteAuthor(hash);

    if (user_id != id_cUser) {
        return -3;
    }

    PasteDBManager::deletePaste(hash);

    return 0;
}