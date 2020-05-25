#include <iostream>

#include <boost/asio.hpp>

#include "tcpclient/TCPClient.h"
#include "server/ALServer.h"
#include "Database.h"

int main(int argc, char* argv[]) {
    Database::getInstance();
    ALServer alServer("127.0.0.1", "3000");

    alServer.run();

    return 0;
}