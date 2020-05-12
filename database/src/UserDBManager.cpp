#include "../include/UserDBManager.h"

#define USER_TABLE_NAME "user_acc"
#define USER_NICKNAME_FIELD "nickname"
#define USER_PASSWORD_FIELD "password"
#define USER_EMAIL_FIELD "email"

void UserDBManager::addUser(const dataFormat &user) {
    storeToDB(user, USER_TABLE_NAME);
}

dataFormat createPKValueMap(const std::string& nickname) {
    return {{USER_NICKNAME_FIELD, nickname}};
}

void UserDBManager::deleteUser(const std::string &nickname) {
    dataFormat pkValueMap = createPKValueMap(nickname);
    deleteByPK(pkValueMap, USER_TABLE_NAME);
}

void UserDBManager::updateUser(const std::string &nickname,
        const dataFormat &newParamsMap) {
    dataFormat pkValueMap = createPKValueMap(nickname);
    updateByPK(pkValueMap, newParamsMap, USER_TABLE_NAME);
}

std::shared_ptr<dataFormat> UserDBManager::getUser(const std::string &username) {
    dataFormat pkValueMap = createPKValueMap(username);
    return getByPK(pkValueMap, USER_TABLE_NAME);
}

bool UserDBManager::isNicknameExist(const std::string &nickname) {
    dataFormat map = {{USER_NICKNAME_FIELD, nickname}};
    std::shared_ptr<dataFormat> result = getByPK(map, USER_TABLE_NAME);
    if (result)
        return true;
    return false;
}

bool UserDBManager::isEmailExist(const std::string &email) {
    dataFormat map = {{USER_EMAIL_FIELD, email}};
    std::shared_ptr<dataFormat> result = getByPK(map, USER_TABLE_NAME);
    if (result)
        return true;
    return false;
}

std::string UserDBManager::getPassword(const std::string& nickname) {
    dataFormat map = {{USER_NICKNAME_FIELD, nickname}};
    std::shared_ptr<dataFormat> result = getByPK(map, USER_TABLE_NAME);
    if (result)
        return (*result)[USER_PASSWORD_FIELD];
    else
        return std::string();
}
