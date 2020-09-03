#include "../include/UserDBManager.h"
#include <chrono>
#include <iomanip>

#define USER_TABLE_NAME "user_acc"
#define USER_NICKNAME_FIELD "nickname"
#define USER_PASSWORD_FIELD "password"
#define USER_EMAIL_FIELD "email"
#define USER_ID_FIELD "user_acc_id"
#define USER_TOKEN_FIELD "token"
#define USER_TOKEN_EXP_TIME_FIELD "token_exp_time"

bool UserDBManager::addUser(const dataFormat &user) {
    return storeToDB(user, USER_TABLE_NAME);
}

const std::string DEFAULT_DAYS_OF_LIVING = "2";
bool UserDBManager::addUser(const std::string &nickname,
                            const std::string &email,
                            const std::string &password,
                            const std::string &token) {
    dataFormat user;
    user[USER_NICKNAME_FIELD] = nickname;
    user[USER_EMAIL_FIELD] = email;
    user[USER_PASSWORD_FIELD] = password;
    user[USER_TOKEN_FIELD] = token;
    user[USER_TOKEN_EXP_TIME_FIELD] = "now() + interval '" + DEFAULT_DAYS_OF_LIVING + "days'";
    return storeToDB(user, USER_TABLE_NAME);
}

conditionMapFormat createConditionMap(const std::string &nickname) {
    return {{USER_NICKNAME_FIELD, SignValue("=", nickname)}};
}

bool UserDBManager::deleteUser(const std::string &nickname) {
    conditionMapFormat pkValueMap = createConditionMap(nickname);
    return updateUser(nickname, {{"is_active", "false"}});
}

bool UserDBManager::updateUser(const std::string &nickname,
                               const dataFormat &newParamsMap) {
    conditionMapFormat pkValueMap = createConditionMap(nickname);
    return updateByPK(pkValueMap, newParamsMap, USER_TABLE_NAME);
}

std::shared_ptr<dataFormat> UserDBManager::getUser(
        const std::string &username) {
    conditionMapFormat pkValueMap = createConditionMap(username);
    return getByPK(pkValueMap, USER_TABLE_NAME);
}

bool UserDBManager::isNicknameExist(const std::string &nickname) {
    conditionMapFormat map = createConditionMap(nickname);
    std::shared_ptr<dataFormat> result = getByPK(map, USER_TABLE_NAME);
    if (result) return true;
    return false;
}

bool UserDBManager::isEmailExist(const std::string &email) {
    conditionMapFormat map = {{USER_EMAIL_FIELD, SignValue("=", email)}};
    std::shared_ptr<dataFormat> result = getByPK(map, USER_TABLE_NAME);
    if (result) return true;
    return false;
}

std::string UserDBManager::getPassword(const std::string &nickname) {
    conditionMapFormat map = createConditionMap(nickname);
    std::shared_ptr<dataFormat> result = getByPK(map, USER_TABLE_NAME);
    if (result)
        return (*result)[USER_PASSWORD_FIELD];
    else
        return std::string();
}

int UserDBManager::getID(const std::string &nickname) {
    conditionMapFormat map = createConditionMap(nickname);
    std::shared_ptr<dataFormat> result =
            getByPK(map, USER_TABLE_NAME, USER_ID_FIELD);
    if (result)
        return std::stoi((*result)[USER_ID_FIELD]);
    else
        return -1;
}

int UserDBManager::isTokenExist(const std::string &token) {
    conditionMapFormat map = {{USER_TOKEN_FIELD, SignValue("=", token)}};
    std::shared_ptr<dataFormat> result = getByPK(map, USER_TABLE_NAME);
    if (result) return std::stoi((*result).at(USER_ID_FIELD));
    return 0;
}

void UserDBManager::updateToken(const std::string &nickname,
                                const std::string &newToken, int daysOfLiving) {
    conditionMapFormat conditionMap = createConditionMap(nickname);
    dataFormat newParamsMap = {
            {USER_TOKEN_FIELD, newToken},
            {USER_TOKEN_EXP_TIME_FIELD, "now() + interval '" + std::to_string(daysOfLiving) + " days'"}};
    updateByPK(conditionMap, newParamsMap, USER_TABLE_NAME);
}
