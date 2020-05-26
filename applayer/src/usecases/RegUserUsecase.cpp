#include "usecases/RegUserUsecase.h"

int RegUserUsecase::execute() {

    bool nicknameIsExist = UserDBManager::isNicknameExist(user.nickname);
    if (nicknameIsExist) {
        return -1;
    }

    bool emailIsExist = UserDBManager::isEmailExist(user.email);
    if (emailIsExist) {
        return -2;
    }
    //генерируем токен
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    std::cout << uuid << std::endl;

    auto tokenValue = boost::lexical_cast<std::string>(uuid);

    token->value = tokenValue;

    UserDBManager::addUser(user.nickname, user.email, user.password, tokenValue);

    return 0;
}