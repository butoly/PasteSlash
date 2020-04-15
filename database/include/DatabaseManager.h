#ifndef DATABASE_DATABASEMANAGER_H
#define DATABASE_DATABASEMANAGER_H

#include "Database.h"
#include "dataFormat.h"

class DatabaseManager {
public:
    DatabaseManager() = default;
    ~DatabaseManager() = default;

    void addPaste(pasteFormat);
    void deletePaste(std::string hash);
    pasteFormat getPaste(std::string hash);

    void addUser(userFormat);
    void deleteUser(std::string username);
    userFormat getUser(std::string username);
};

#endif // DATABASE_DATABASEMANAGER_H
