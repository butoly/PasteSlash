#ifndef URL_GEN_SESSION_H
#define URL_GEN_SESSION_H

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>

#include "KeyGenerator.h"

using namespace boost::asio;

class SessionClass
        : public std::enable_shared_from_this<SessionClass>
{
public:
    SessionClass(ip::tcp::socket socket, std::shared_ptr<KeyGeneratorClass> keyGenerator);
    ~SessionClass() = default;
    void start();

private:
    void doRead();
    void onRead();
    void doWrite();
    void onWrite();

    ip::tcp::socket socket;
    streambuf readBuffer;
    streambuf writeBuffer;

    std::shared_ptr<KeyGeneratorClass> keyGenerator;
};

#endif //URL_GEN_SESSION_H
