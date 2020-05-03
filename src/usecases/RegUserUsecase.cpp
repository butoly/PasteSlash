#include "usecases/RegUserUsecase.h"

void RegUserUsecase::execute() {
    try {
        Application::getInstance().regUser();
    } catch(std::exception& e) {
    }
}