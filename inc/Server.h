#ifndef URL_GEN_SERVER_H
#define URL_GEN_SERVER_H

#include <iostream>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <thread>
#include <boost/asio.hpp>

#include "../inc/Session.h"
#include "../inc/KeyGenerator.h"

using namespace boost::asio;

class ServerClass
{
public:
    ServerClass(boost::asio::ip::address address, unsigned short port);
    void run();
private:
    void accept();
    ip::tcp::endpoint endpoint;
    io_service service;
    ip::tcp::acceptor acceptor;
    ip::tcp::socket socket;

    KeyGeneratorClass *keyGenerator;
};

#endif //URL_GEN_SERVER_H
