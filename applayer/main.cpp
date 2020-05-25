#include <iostream>

#include <boost/asio.hpp>

#include "tcpclient/TCPClient.h"
#include "server/ALServer.h"

int main(int argc, char* argv[]) {

//    std::cout << "server started " << std::endl;
//
//    TCPServer serv;
//
//    serv.start("127.0.0.1", 3000);
//    TCPClient client("127.0.0.1", 3000);
//
//    std::string s = "{\"command\": \"get hash\", \"body\": {}}";
//
//    auto error = client.connect();
//    if (error != boost::system::errc::success) {
//    }
//
//    auto receivedData = client.send(s);


    ALServer alServer("127.0.0.1", "3000");

    alServer.run();

    return 0;
}