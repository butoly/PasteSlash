#ifndef PROJECT_TCPSERVER_H
#define PROJECT_TCPSERVER_H

#include <iostream>

#include "Socket.h"

class TCPServer {
    Socket socket;
    std::string address;
    int port;
public:
    TCPServer(std::string address, int port): socket(address, port) {}

    void accept(); // connection shared_from_this()
    void listen();
};

#endif //PROJECT_TCPSERVER_H
