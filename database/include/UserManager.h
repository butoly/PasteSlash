#ifndef DATABASE_USERMANAGER_H
#define DATABASE_USERMANAGER_H

#include "dataFormat.h"
#include "gmock/gmock.h"

class BaseUserManager {
public:
    virtual ~BaseUserManager() = 0;
    virtual void addUser(userFormat) = 0;
    virtual void deleteUser(std::string) = 0;
    virtual userFormat getUser(std::string) = 0;
};

class UserManager : BaseUserManager {
public:
    ~UserManager() = default;
    void addUser(userFormat) override;
    void deleteUser(std::string user_name) override;
    userFormat getUser(std::string user_name) override;
};

class MockUserManager : BaseUserManager {
public:
    MOCK_METHOD1(addUser, void (userFormat));
    MOCK_METHOD1(deleteUser, void (std::string));
    MOCK_METHOD1(getUser, userFormat (std::string));
};

#endif // DATABASE_USERMANAGER_H
