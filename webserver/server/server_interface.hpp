#ifndef WEBSERVER_SERVER_INTERFACE_HPP
#define WEBSERVER_SERVER_INTERFACE_HPP

#include <boost/noncopyable.hpp>

namespace pasteslash {
namespace webserver {
namespace server {

class IHttpServer : boost::noncopyable {
public:
    IHttpServer(const IHttpServer&) = delete;
    IHttpServer& operator=(const IHttpServer&) = delete;
    virtual ~IHttpServer() = default;

    virtual void run() = 0;

private:
    virtual void do_accept() = 0;
    virtual void do_await_stop() = 0;
};

} // server
} // webserver
} // pasteslash

#endif // WEBSERVER_SERVER_INTERFACE_HPP
