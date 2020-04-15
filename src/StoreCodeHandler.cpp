#include "../inc/StoreCodeHandler.h"

void StoreCodeHandler::execute() {
    std::string data;

    try {
        Application::getInstance().storeCode(data);
    } catch(std::exception& e) {

    }
}