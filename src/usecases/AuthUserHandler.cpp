#include "usecases/AuthUserHandler.h"


void AuthUserHandler::execute() {
    try {
        Application::getInstance().authUser();
    } catch(std::exception& e) {
}
}