#include <iostream>

#include <boost/asio.hpp>

#include "TCPServer.h"
#include "Connection.h"
#include "TCPClient.h"

int main(int argc, char* argv[]) {

    std::cout << "server started " << std::endl;

    TCPServer serv;

    serv.start("127.0.0.1", 3000);
    return 0;
}