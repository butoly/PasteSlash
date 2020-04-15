#ifndef PROJECT_CONNECTION_H
#define PROJECT_CONNECTION_H

#include <iostream>


#include "Socket.h"
#include "RequestManager.h"

class Connection : public std::enable_shared_from_this<Connection> {
private:
    struct Sender {
        Sender(Connection& c) : conn(c) {
        }

        Connection& conn;

        void send() {
            conn.write();
        }
    };

    Socket sct;
    RequestManager<Sender> rm;

public:
    Connection(Socket _sct) : sct(std::move(_sct)), rm(Sender(*this)) {}
    ~Connection() {}

    void read();
    void write();
};

#endif //PROJECT_CONNECTION_H
