#include "../inc/GetCodeHandler.h"


void GetCodeHandler::execute() {
    try {
        Application::getInstance().getCode();
    } catch(std::exception& e) {
// e.what();
// delete pointers if necessary
    }
}