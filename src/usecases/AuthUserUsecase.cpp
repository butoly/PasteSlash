#include "usecases/AuthUserUsecase.h"


int AuthUserUsecase::execute() {
    //заглушка для проверки, есть ли такой ник вообще в бд
    bool hasN = true;
    if (!hasN) {
        return -1;
    }

    //заглушка для проверки, правильные ли данные
    bool isValidate = true;
    if (!isValidate) {
        return -2;
    }

    //достаем из бд токен/ генерируем и сохраняем в бд


    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    std::cout << uuid << std::endl;

    auto tokenValue = boost::lexical_cast<std::string>(uuid);

    token->value = tokenValue;

    return 0;
}