#ifndef PROJECT_TCPCLIENT_H
#define PROJECT_TCPCLIENT_H

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>

using namespace boost::asio;

class TCPClient {
    // Объект для работы с операциями ввода/вывода операционной системы
    io_context ioc;
    ip::tcp::socket socket;
    char buffer[1024];
    ip::tcp::endpoint ep;

public:
    TCPClient(const char* addr, unsigned short port): socket(ioc), ep(ip::make_address(addr), port) {
        memset(buffer, 0, sizeof(buffer));
    }

    boost::system::errc::errc_t connect();

    std::string send(std::string& msg);

private:
    std::string receive();
};

#endif //PROJECT_TCPCLIENT_H
