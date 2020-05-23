#include "usecases/RegUserUsecase.h"

int RegUserUsecase::execute() {
    //заглушка для проверки, есть ли такой ник уже в бд
    bool hasN;
    if (hasN) {
        return -1;
    }
    //заглушка для проверки, есть ли такой mail уже в бд
    bool hasE;
    if (hasE) {
        return -2;
    }
    //генерируем из бд токен
    std::string tokenValue = "token";

    token.value = tokenValue;

    return 0;
}