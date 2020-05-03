#include "usecases/StoreCodeUsecase.h"

void StoreCodeUsecase::execute() {
    std::string data;

    try {
        Application::getInstance().storeCode(data);
    } catch(std::exception& e) {

    }
}