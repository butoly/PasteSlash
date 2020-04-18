#include "../inc/Server.h"

Server::Server() {

}

Server::~Server() {

}

std::string Server::read_(tcp::socket & socket) {
    boost::asio::streambuf buf;
    boost::asio::read_until( socket, buf, "\n" );
    std::string data = boost::asio::buffer_cast<const char*>(buf.data());
    return data;
}

void Server::send_(tcp::socket & socket, const std::string& message) {
    const std::string msg = message + "\n";
    boost::asio::write( socket, boost::asio::buffer(message) );
}