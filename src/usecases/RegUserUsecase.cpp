#include "usecases/RegUserUsecase.h"

int RegUserUsecase::execute() {
    //заглушка для проверки, есть ли такой ник уже в бд
    bool hasN = false;
    if (hasN) {
        return -1;
    }
    //заглушка для проверки, есть ли такой mail уже в бд
    bool hasE = false;
    if (hasE) {
        return -2;
    }
    //генерируем из бд токен
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    std::cout << uuid << std::endl;

    auto tokenValue = boost::lexical_cast<std::string>(uuid);

    token->value = tokenValue;

    return 0;
}