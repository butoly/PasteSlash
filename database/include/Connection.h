#ifndef DATABASE_CONNECTION_H
#define DATABASE_CONNECTION_H

#include <iostream>
//#include "libpq-fe.h"

class Connection {
public:
    Connection(std::string configFileName);
    ~Connection();

    bool isActive();

private:
    //PGconn* connection;
};

#endif //DATABASE_CONNECTION_H
