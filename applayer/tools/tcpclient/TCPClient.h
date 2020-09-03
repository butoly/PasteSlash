#ifndef PROJECT_TCPCLIENT_H
#define PROJECT_TCPCLIENT_H

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <iostream>

using namespace boost::asio;
using boost::lambda::var;
using boost::lambda::_1;

class TCPClient {
    // Объект для работы с операциями ввода/вывода операционной системы
    io_context ioc;
    ip::tcp::socket socket;
    char buffer[1024];
    ip::tcp::endpoint ep;
    deadline_timer timer;
    ip::tcp::resolver::iterator iter;


public:
    TCPClient(const char* addr, const char* port): socket(ioc), timer(ioc) {
        memset(buffer, 0, sizeof(buffer));
        ip::tcp::resolver resolver(ioc);
        ip::tcp::resolver::query query(addr,  port);
        iter = resolver.resolve(query);
        ep = *iter;
        timer.expires_at(boost::posix_time::pos_infin);
        checkDeadline();
    }

    boost::system::errc::errc_t connect();

    std::string send(std::string& msg);

private:
    std::string receive();

    void checkDeadline();
};

#endif //PROJECT_TCPCLIENT_H
