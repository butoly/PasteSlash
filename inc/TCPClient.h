#ifndef PROJECT_TCPCLIENT_H
#define PROJECT_TCPCLIENT_H

#include <iostream>

#include "Socket.h"

class TCPClient {
private:
    Socket socket;
public:
    TCPClient(Socket socket) : socket(socket) {}
    ~TCPClient() {}

    void connect(const std::string &host, int port) throw (std::exception);
    void send(const std::string &s) throw (std::exception);
    std::string recv() throw (std::exception);
};


#endif //PROJECT_TCPCLIENT_H
