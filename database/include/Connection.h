#ifndef CONNECTION_H
#define CONNECTION_H

#include <pqxx/pqxx>
#include <pqxx/transaction>
#include "dataFormat.h"

class Connection {
public:
    Connection();
    explicit Connection(const std::string& configFileName);
    ~Connection() = default;

    bool isActive();

    bool execPostQuery(const std::string& sqlQuery);
    void execPostQueryFromFile(const std::string &fileName);
    queryResultFormat execGetQuery(const std::string& sqlQuery);
    queryResultFormat execGetQueryFromFile(const std::string& fileName);

private:
    pqxx::connection connection;
};

#endif //CONNECTION_H
