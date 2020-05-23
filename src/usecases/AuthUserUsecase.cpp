#include "usecases/AuthUserUsecase.h"


int AuthUserUsecase::execute() {
    //заглушка для проверки, есть ли такой ник вообще в бд
    bool hasN;
    if (!hasN) {
        return -1;
    }

    //заглушка для проверки, правильные ли данные
    bool isValidate;
    if (!isValidate) {
        return -2;
    }

    //достаем из бд токен/ генерируем и сохраняем в бд
    std::string tokenValue = "token";

    token.value = tokenValue;

    return 0;
}