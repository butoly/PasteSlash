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

public:
    TCPClient(): socket(ioc) {
        memset(buffer, 0, sizeof(buffer));
    }

    std::string run(const char* addr, unsigned short port, std::string& msg);

private:
    std::string send(std::string& msg);

    std::string receive();
};

#endif //PROJECT_TCPCLIENT_H
