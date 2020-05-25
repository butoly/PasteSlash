#ifndef URL_GEN_SERVER_H
#define URL_GEN_SERVER_H

#include <iostream>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <thread>
#include <boost/asio.hpp>

#include "Session.h"
#include "KeyGenerator.h"

using namespace boost::asio;

class ServerClass
{
public:
    ServerClass(const boost::asio::ip::address& address, unsigned short port);
    void run();
private:
    void accept();
    ip::tcp::endpoint endpoint;
    io_service service;
    ip::tcp::acceptor acceptor;
    ip::tcp::socket socket;

    std::shared_ptr<KeyGeneratorClass> keyGenerator;
};

#endif //URL_GEN_SERVER_H
