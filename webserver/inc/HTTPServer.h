#ifndef WEBSERVER_HTTP_SERVER_HPP
#define WEBSERVER_HTTP_SERVER_HPP

#include <boost/beast/core.hpp>
#include <boost/noncopyable.hpp>
#include <memory>
#include <string>

namespace net = boost::asio;

// HTTP server for receiving user requests
class HTTPServer : boost::noncopyable {
public:
    HTTPServer(std::string address, std::string port, int threads = 1);

    // Start running server
    void run();

private:
    unsigned short threads_;
    net::io_context ioc_;
};

#endif // WEBSERVER_HTTP_SERVER_HPP
