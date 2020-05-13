#ifndef WEBSERVER_TCP_CLIENT_HPP
#define WEBSERVER_TCP_CLIENT_HPP

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/steady_timer.hpp>
#include <string>

#include "tcp_client_interface.hpp"
#include "../utils/output.hpp"

using boost::asio::steady_timer;
using boost::asio::ip::tcp;

namespace pasteslash {
namespace webserver {
namespace client {

// TCP client for communication with Application Layer
template<class Send>
class TcpClient : public ITcpClient {
public:
    TcpClient();
    TcpClient(boost::asio::io_context& io_context, const Send& callback,
        const std::string& msg);

    TcpClient(const TcpClient&) = delete;
    TcpClient& operator=(const TcpClient&) = delete;
    virtual ~TcpClient() = default;

    // Start connecting and set deadline
    void start() override;

    // Stop connecting
    void stop() override;

private:
    // Connect to server
    void start_connect(tcp::resolver::results_type::iterator endpoint_iter);

    // Handle connection
    void handle_connect(const boost::system::error_code& ec,
        tcp::resolver::results_type::iterator endpoint_iter);
    
    // Write request
    void start_write();

    // Handle writing
    void handle_write(const boost::system::error_code& ec);

    // Read response
    void start_read();

    // Handle reading
    void handle_read(const boost::system::error_code& ec,
        unsigned int n);
    
    // Check current time for deadline
    void check_deadline();

    bool stopped_ = false;
    tcp::resolver::results_type endpoints_;
    tcp::socket socket_;
    std::string input_buffer_;
    steady_timer deadline_;
    std::string msg_;
    Send send_;
    const std::string error_msg_ = "Server error";
};

} // client
} // webserver
} // pasteslash

#include "tcp_client.inl"

#endif // WEBSERVER_TCP_CLIENT_HPP
