#include "usecases/AuthUserUsecase.h"


int AuthUserUsecase::execute() {

    bool isFound = UserDBManager::isNicknameExist(user.nickname);
    if (!isFound) {
        return -1;
    }

    std::string password = UserDBManager::getPassword(user.nickname);
    if (user.password != password) {
        return -2;
    }

    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    std::cout << uuid << std::endl;

    auto tokenValue = boost::lexical_cast<std::string>(uuid);

    token->value = tokenValue;

    UserDBManager::updateToken(user.nickname, tokenValue);

    return 0;
}