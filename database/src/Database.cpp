#include "../include/Database.h"
#define TESTING 1

Database::Database():
    connection()
    {}

Database& Database::getInstance(){
    static Database instance;
    return instance;
}

void Database::execPostQuery(const std::string& sqlQuery) {
    connection.execPostQuery(sqlQuery);
}

queryResultFormat Database::execGetQuery(const std::string& sqlQuery) {
    return connection.execGetQuery(sqlQuery);
}
