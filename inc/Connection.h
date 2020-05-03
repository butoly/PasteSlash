#ifndef PROJECT_CONNECTION_H
#define PROJECT_CONNECTION_H

#include <iostream>
#include "RequestHandler.h"

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

using namespace boost;
using namespace boost::asio;

class Connection : public std::enable_shared_from_this<Connection> {
private:
    ip::tcp::socket socket;
    RequestHandler rm;
    char buffer[1024];

    void write();

    void onWrite(const boost::system::error_code& e) {
        memset(buffer, 0, sizeof(buffer));
        socket.cancel();
        socket.shutdown(ip::tcp::socket::shutdown_both);
        socket.close();
    }

    // Асинхронно читаем из сокета пришедшие данные
    void read();

    // callback функция для чтения
    void onRead(const boost::system::error_code& e, std::size_t bytesTransferred);

    std::size_t completion_condition(const boost::system::error_code& error, std::size_t bytes_transferred) {
        if (bytes_transferred > 0) {
            return 0;
        }

        return sizeof(buffer);
    }

public:
    explicit Connection(boost::asio::io_context& io) : socket(io) {}

    boost::asio::ip::tcp::socket& getSocket() {
        return socket;
    }

    void process() {
        read();
    }
};

#endif //PROJECT_CONNECTION_H
