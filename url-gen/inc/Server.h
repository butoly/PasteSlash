#ifndef URL_GEN_SERVER_H
#define URL_GEN_SERVER_H
#include <boost/asio.hpp>
#include <iostream>

using namespace boost::asio;
using ip::tcp;

class Server {
public:
    Server();
    ~Server();
    std::string read_(tcp::socket & socket);
    void send_(tcp::socket & socket, const std::string& message);
private:
};

#endif //URL_GEN_SERVER_H
