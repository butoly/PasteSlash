#include "usecases/DeleteCodeHandler.h"

void DeleteCodeHandler::execute() {
    try {
        Application::getInstance().deleteCode();
    } catch(std::exception& e) {
// e.what();
// delete pointers if necessary
    }
}