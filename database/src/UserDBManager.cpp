#include "../include/UserDBManager.h"

#define USER_TABLE_NAME "user_acc"
#define USER_USERNAME_FIELD "username"

void UserDBManager::addUser(const dataFormat &user) {
    storeToDB(user, USER_TABLE_NAME);
}

dataFormat createPKValueMap(const std::string& username) {
    return {{USER_USERNAME_FIELD, username}};
}

void UserDBManager::deleteUser(const std::string &username) {
    dataFormat pkValueMap = createPKValueMap(username);
    deleteByPK(pkValueMap, USER_TABLE_NAME);
}

void UserDBManager::updateUser(const std::string &username,
                               const dataFormat &newParamsMap) {
    dataFormat pkValueMap = createPKValueMap(username);
    updateByPK(pkValueMap, newParamsMap, USER_TABLE_NAME);
}

std::shared_ptr<dataFormat> UserDBManager::getUser(const std::string &username) {
    dataFormat pkValueMap = createPKValueMap(username);
    return getByPK(pkValueMap, USER_TABLE_NAME);
}
