#ifndef WEBSERVER_TCP_CLIENT_HPP
#define WEBSERVER_TCP_CLIENT_HPP

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/steady_timer.hpp>
#include <string>

#include "tcp_client_interface.hpp"

using boost::asio::steady_timer;
using tcp = boost::asio::ip::tcp;

namespace pasteslash {
namespace webserver {
namespace client {

template<class Send>
class TcpClient : public ITcpClient {
public:
    TcpClient(const TcpClient&) = delete;
    TcpClient& operator=(const TcpClient&) = delete;
    virtual ~TcpClient() = default;

    TcpClient() = default;
    TcpClient(const std::string data, Send&& send);

    void start() override;
    void stop() override;

private:
    void handle_connect(const boost::system::error_code& ec,
        tcp::resolver::results_type::iterator endpoint_iter) override;
    
    void start_write(const boost::system::error_code& ec) override;

    void handle_write(const boost::system::error_code& ec) override;

    void start_read(const boost::system::error_code& ec) override;

    void handle_read(const boost::system::error_code& ec) override;
    
    void check_deadline();

    bool stopped_ = false;
    tcp::resolver::results_type endpoints_;
    tcp::socket socket_;
    std::string input_buffer_;
    steady_timer deadline_;
    steady_timer heartbeat_timer_;
};

} // client
} // webserver
} // pasteslash

#endif // WEBSERVER_TCP_CLIENT_HPP
