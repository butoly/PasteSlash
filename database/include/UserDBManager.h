#ifndef TEST_USERDBMANAGER_H
#define TEST_USERDBMANAGER_H

#include "DatabaseObject.h"

class UserDBManager: public DatabaseObject {
public:
    static void addUser(const dataFormat& user);
    static void deleteUser(const std::string& username);
    static void updateUser(const std::string& username, const dataFormat& newParamsMap);
    static std::shared_ptr<dataFormat> getUser(const std::string& username);
};

#endif //TEST_USERDBMANAGER_H
