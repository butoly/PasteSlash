#ifndef WEBSERVER_CLIENT_HPP
#define WEBSERVER_CLIENT_HPP

#include <boost/noncopyable.hpp>
#include <boost/asio/ip/tcp.hpp>

using tcp = boost::asio::ip::tcp;

namespace pasteslash {
namespace webserver {
namespace client {

class ITcpClient : boost::noncopyable {
public:
    ITcpClient(const ITcpClient&) = delete;
    ITcpClient& operator=(const ITcpClient&) = delete;
    virtual ~ITcpClient() = default;

    virtual void start() = 0;
    virtual void stop() = 0;

private:
    virtual void handle_connect(const boost::system::error_code& ec,
        tcp::resolver::results_type::iterator endpoint_iter) = 0;

    virtual void start_write(const boost::system::error_code& ec) = 0;
    virtual void handle_write(const boost::system::error_code& ec) = 0;
    virtual void start_read(const boost::system::error_code& ec) = 0;
    virtual void handle_read(const boost::system::error_code& ec) = 0;
};

} // namespace client
} // namespace webserver
} // namespace pasteslash

#endif // WEBSERVER_CLIENT_HPP
