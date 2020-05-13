#ifndef WEBSERVER_SESSION_INTERFACE_HPP
#define WEBSERVER_SESSION_INTERFACE_HPP

#include <boost/noncopyable.hpp>
#include <boost/beast/core.hpp>

namespace beast = boost::beast;

namespace pasteslash {
namespace webserver {
namespace session {

class ISession : boost::noncopyable {
public:
    ISession() = default;
    
    ISession(const ISession&) = delete;
    ISession& operator=(const ISession&) = delete;
    virtual ~ISession() = default;

    virtual void run() = 0;
    virtual void do_read() = 0;
    virtual void on_read(beast::error_code ec, std::size_t bytes_transferred) = 0;
};

} // session
} // webserver
} // pasteslash

#endif // WEBSERVER_SESSION_INTERFACE_HPP
