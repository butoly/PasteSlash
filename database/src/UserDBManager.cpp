#include "../include/UserDBManager.h"

#define USER_TABLE_NAME "user_acc"
#define USER_NICKNAME_FIELD "nickname"
#define USER_PASSWORD_FIELD "password"
#define USER_EMAIL_FIELD "email"

void UserDBManager::addUser(const dataFormat &user) {
    storeToDB(user, USER_TABLE_NAME);
}

conditionMapFormat createPKValueMap(const std::string& nickname) {
    return {{USER_NICKNAME_FIELD, SignValue("=", nickname)}};
}

void UserDBManager::deleteUser(const std::string &nickname) {
    conditionMapFormat pkValueMap = createPKValueMap(nickname);
    deleteByPK(pkValueMap, USER_TABLE_NAME);
}

void UserDBManager::updateUser(const std::string &nickname,
        const dataFormat &newParamsMap) {
    conditionMapFormat pkValueMap = createPKValueMap(nickname);
    updateByPK(pkValueMap, newParamsMap, USER_TABLE_NAME);
}

std::shared_ptr<dataFormat> UserDBManager::getUser(const std::string &username) {
    conditionMapFormat pkValueMap = createPKValueMap(username);
    return getByPK(pkValueMap, USER_TABLE_NAME);
}

bool UserDBManager::isNicknameExist(const std::string &nickname) {
    conditionMapFormat map = createPKValueMap(nickname);
    std::shared_ptr<dataFormat> result = getByPK(map, USER_TABLE_NAME);
    if (result)
        return true;
    return false;
}

bool UserDBManager::isEmailExist(const std::string &email) {
    conditionMapFormat map = {{USER_EMAIL_FIELD, SignValue("=", email)}};
    std::shared_ptr<dataFormat> result = getByPK(map, USER_TABLE_NAME);
    if (result)
        return true;
    return false;
}

std::string UserDBManager::getPassword(const std::string& nickname) {
    conditionMapFormat map = createPKValueMap(nickname);
    std::shared_ptr<dataFormat> result = getByPK(map, USER_TABLE_NAME);
    if (result)
        return (*result)[USER_PASSWORD_FIELD];
    else
        return std::string();
}
