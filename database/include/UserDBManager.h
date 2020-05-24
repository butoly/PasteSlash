#ifndef TEST_USERDBMANAGER_H
#define TEST_USERDBMANAGER_H

#include "DatabaseObject.h"

class UserDBManager: public DatabaseObject {
public:
    static void addUser(const dataFormat& user);
    static void addUser(const std::string& nickname, const std::string& email,
            const std::string& password, const std::string& token);
    static void deleteUser(const std::string& nickname);
    static void updateUser(const std::string& nickname, const dataFormat& newParamsMap);
    static std::shared_ptr<dataFormat> getUser(const std::string& username);

    static bool isNicknameExist(const std::string& nickname);
    static bool isEmailExist(const std::string &email);
    static int getID(const std::string& nickname);
    static std::string getPassword(const std::string &nickname);

    static void updateToken(const std::string& nickname, const std::string &newToken, int dayOfLiving=2);
    static bool isTokenExist(const std::string &token);
};

#endif //TEST_USERDBMANAGER_H
