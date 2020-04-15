#include <boost/noncopyable.hpp>

#ifndef WEBSERVER_CLIENT_HPP
#define WEBSERVER_CLIENT_HPP



#include "client_interface.hpp"

namespace pasteslash {
namespace webserver {
namespace client {

class ITcpClient : boost::noncopyable {
public:
    ITcpClient(const ITcpClient&) = delete;
    ITcpClient& operator=(const ITcpClient&) = delete;
    virtual ~ITcpClient() = default;

    virtual void open_connection() = 0;
    virtual void close_connection() = 0;

private:
    virtual void do_connect() = 0;
    virtual void do_send() = 0;
    virtual void do_recieve() = 0;
    virtual void do_close() = 0;
};

} // namespace client
} // namespace webserver
} // namespace pasteslash

#endif // WEBSERVER_CLIENT_HPP
