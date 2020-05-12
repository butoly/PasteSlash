#ifndef WEBSERVER_HTTP_SERVER_HPP
#define WEBSERVER_HTTP_SERVER_HPP

#include <boost/beast/core.hpp>
#include <boost/noncopyable.hpp>
#include <memory>
#include <string>

#include "../listener/listener.hpp"

namespace net = boost::asio;

namespace pasteslash {
namespace webserver {
namespace server {

// HTTP server for receiving user requests
class HttpServer : boost::noncopyable {
public:
    HttpServer(std::string address, std::string port, int threads = 1);

    // Start running server
    void run();

private:
    unsigned short threads_;
    net::io_context ioc;
};

} // server
} // webserver
} // pasteslash

#endif // WEBSERVER_HTTP_SERVER_HPP
