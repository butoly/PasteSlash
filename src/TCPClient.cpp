#include "TCPClient.h"

std::string TCPClient::run(const char* addr, unsigned short port, std::string& msg) {
    // Определяем endpoint
    ip::tcp::endpoint ep(ip::make_address(addr), port);
    boost::system::error_code error;

    socket.connect(ep, error);
    if (error) {
        std::cout << "client terminated " << error.message() << std::endl;
    }
    std::string data = send(msg);

    std::cout << data << "TCPClient" << std::endl;
    return data;
}

std::string TCPClient::send(std::string& msg) {

    boost::system::error_code error;
    write(socket, boost::asio::buffer(msg), error);
    if(error) {
        std::cout << "send failed: " << error.message() << std::endl;
    }

    return receive();
}

std::string TCPClient::receive() {
    streambuf receive_buffer;
    boost::system::error_code error;

    read(socket, receive_buffer, transfer_all(), error);
    if (error && error != boost::asio::error::eof) {
        std::cout << "receive failed: " << error.message() << std::endl;
    }
    std::string s( (std::istreambuf_iterator<char>(&receive_buffer)), std::istreambuf_iterator<char>() );
    std::cout <<"RECIEVE" << std::endl;
    return s;
}