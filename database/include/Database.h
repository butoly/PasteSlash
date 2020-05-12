#ifndef DATABASE_DATABASE_H
#define DATABASE_DATABASE_H

#include <iostream>
#include "dataFormat.h"
#include "Connection.h"

class Database {
public:
    static Database& getInstance();

    void execPostQuery(const std::string& sqlQuery);
    queryResultFormat execGetQuery(const std::string& sqlQuery);

    Database(const Database&) = delete;
    Database(Database&&) = delete;
    void operator = (const Database&) = delete;
    void operator = (Database&&) = delete;

protected:
    Database();
    Connection connection;
};

#endif //DATABASE_DATABASE_H
