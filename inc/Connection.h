#ifndef PROJECT_CONNECTION_H
#define PROJECT_CONNECTION_H

#include <iostream>
#include "RequestManager.h"

#include <boost/asio.hpp>
#include <boost/bind.hpp>

using namespace boost;
using namespace boost::asio;

class Connection : public std::enable_shared_from_this<Connection> {
private:
    ip::tcp::socket socket;
    RequestManager rm;
    char buffer[1024];

    void write() {
        socket.async_write_some(asio::buffer(buffer), boost::bind(&Connection::onWrite, shared_from_this(),
                                                                  boost::asio::placeholders::error));
    }

    void onWrite(const boost::system::error_code& e) {
        std::cout << buffer << std::endl;
        socket.close();
    }

    // Асинхронно читаем из сокета пришедшие данные
    void read() {
        socket.async_read_some(asio::buffer(buffer), boost::bind(&Connection::onRead, shared_from_this(),
                                                                 boost::asio::placeholders::error,
                                                                 boost::asio::placeholders::bytes_transferred));
    }

    // callback функция для чтения
    void onRead(const boost::system::error_code& e, std::size_t bytesTransferred) {
        if (e) {
            return;
        }

        if (e == boost::asio::error::eof) {
            std::cerr << "-connection: " << socket.remote_endpoint().address().to_string() << std::endl;
        }

        write();
    }

public:
    explicit Connection(boost::asio::io_service& io) : socket(io) {}

    boost::asio::ip::tcp::socket& getSocket() {
        return socket;
    }

    void process() {
        read();
    }
};

#endif //PROJECT_CONNECTION_H
