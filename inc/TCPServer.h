#ifndef PROJECT_TCPSERVER_H
#define PROJECT_TCPSERVER_H

#include <iostream>
#include "Connection.h"

using namespace boost::asio;

class TCPServer {
    // Объект для работы с операциями ввода/вывода операционной системы
    io_context ioc;

    // Сокет, слушающий соединения
    ip::tcp::acceptor acceptor;

    void listen();

    // callback функция для обработки пришедшего соединения
    void onAccept(std::shared_ptr<Connection> conn, const boost::system::error_code& ec);

    void run() {
        ioc.run();
    }

public:
    TCPServer() : acceptor(ioc) {}

    ~TCPServer() {
        acceptor.close();
    }

    void start(const char* addr, unsigned short port);
};

#endif //PROJECT_TCPSERVER_H
