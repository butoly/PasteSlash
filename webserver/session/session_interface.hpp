#ifndef WEBSERVER_SESSION_INTERFACE_HPP
#define WEBSERVER_SESSION_INTERFACE_HPP

#include <boost/noncopyable.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <iostream>
#include <memory>
#include <string>

#include "../request/handler_request.hpp"

namespace beast = boost::beast;
namespace http = beast::http;
using tcp = boost::asio::ip::tcp;

namespace pasteslash {
namespace webserver {
namespace session {

class ISession : boost::noncopyable {
public:
    ISession(const ISession&) = delete;
    ISession& operator=(const ISession&) = delete;
    virtual ~ISession() = default;

    ISession() = default;

    virtual void run() = 0;
    virtual void do_read() = 0;
    virtual void on_read(beast::error_code ec, std::size_t bytes_transferred) = 0;
};

} // session
} // webserver
} // pasteslash

#endif // WEBSERVER_SESSION_INTERFACE_HPP
