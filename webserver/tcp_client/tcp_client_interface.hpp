#ifndef WEBSERVER_CLIENT_HPP
#define WEBSERVER_CLIENT_HPP

#include <boost/noncopyable.hpp>

namespace pasteslash {
namespace webserver {
namespace client {

class ITcpClient : boost::noncopyable {
public:
    ITcpClient() = default;

    ITcpClient(const ITcpClient&) = delete;
    ITcpClient& operator=(const ITcpClient&) = delete;
    virtual ~ITcpClient() = default;

    virtual void start() = 0;
    virtual void stop() = 0;
};

} // namespace client
} // namespace webserver
} // namespace pasteslash

#endif // WEBSERVER_CLIENT_HPP
