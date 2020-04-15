#ifndef DATABASE_DATABASE_H
#define DATABASE_DATABASE_H

#include <iostream>
#include "vector"
#include "dataFormat.h"
#include "Connection.h"
#include "gmock/gmock.h"

class DatabaseInterface {
public:
    virtual ~DatabaseInterface() = 0;
    virtual void execQuery(std::string sql_query) = 0;
    virtual dataFormat execGetQuery(std::string sql_query) = 0;
};

class Database : public DatabaseInterface {
public:
    static Database& getInstance();

    Database(const Database&) = delete;
    Database(Database&&) = delete;
    void operator = (const Database&) = delete;
    void operator = (Database&&) = delete;

    void execQuery(std::string sql_query) override;
    dataFormat execGetQuery(std::string sql_query) override;

protected:
    Database();
    ~Database();
    static Database& instance;
    Connection connection;
};

class MockDatabase : public DatabaseInterface {
public:
    MOCK_METHOD1(execQuery, void(const std::string sql_query)) {};
};

#endif //DATABASE_DATABASE_H
