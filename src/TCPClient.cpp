#include "TCPClient.h"

boost::system::errc::errc_t TCPClient::connect() {
    boost::system::error_code error;

    socket.connect(ep, error);
    if (error) {
        std::cout << "client terminated " << error.message() << std::endl;
        return boost::system::errc::not_connected;
    }
    return boost::system::errc::success;
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