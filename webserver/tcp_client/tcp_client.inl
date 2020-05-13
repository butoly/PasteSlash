#ifndef WEBSERVER_TCP_CLIENT_INL
#define WEBSERVER_TCP_CLIENT_INL

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/write.hpp>
#include <string>

#include "tcp_client.hpp"

using boost::asio::steady_timer;
using boost::asio::ip::tcp;
using std::placeholders::_1;
using std::placeholders::_2;

namespace pasteslash {
namespace webserver {
namespace client {

template<class Send>
TcpClient<Send>::TcpClient(boost::asio::io_context& io_context,
    const Send& callback, const std::string& msg) :
socket_(io_context),
deadline_(io_context),
msg_(msg),
send_(callback) {
    tcp::resolver resolver(io_context);
    // TODO: make it via config file
    endpoints_ = resolver.resolve("127.0.0.1", "8080");
}

template<class Send>
void TcpClient<Send>::start() {
    start_connect(endpoints_.begin());
    deadline_.async_wait(std::bind(&TcpClient::check_deadline, this));
}

template<class Send>
void TcpClient<Send>::stop() {
    stopped_ = true;
    boost::system::error_code ignored_ec;
    socket_.close(ignored_ec);
    deadline_.cancel();
}

template<class Send>
void TcpClient<Send>::start_connect(
    tcp::resolver::results_type::iterator endpoint_iter) {
    if (endpoint_iter != endpoints_.end()) {
        deadline_.expires_after(std::chrono::seconds(60));
        socket_.async_connect(endpoint_iter->endpoint(), std::bind(
            &TcpClient::handle_connect, this, _1, endpoint_iter));
    } else {
        stop();
    }
}

template<class Send>
void TcpClient<Send>::handle_connect(const boost::system::error_code& ec,
    tcp::resolver::results_type::iterator endpoint_iter) {
    if (stopped_) {
        return;
    }
    if (!socket_.is_open()) {
        start_connect(++endpoint_iter);
    } else if (ec) {
        utils::fail(ec, "tcp-client connect");
        socket_.close();
        start_connect(++endpoint_iter);
        send_(error_msg_);
    } else {
        start_write();
        start_read();
    }
}

template<class Send>
void TcpClient<Send>::start_write() {
    if (stopped_) {
        return;
    }
    boost::asio::async_write(socket_, boost::asio::buffer(msg_.c_str(),
        msg_.size()), std::bind(&TcpClient::handle_write, this, _1));
}

template<class Send>
void TcpClient<Send>::handle_write(const boost::system::error_code& ec) {
    if (stopped_) {
        return;
    }
    if (ec) {
        utils::fail(ec, "tcp-client write");
        stop();
        send_(error_msg_);
    }
}

template<class Send>
void TcpClient<Send>::start_read() {
    deadline_.expires_after(std::chrono::seconds(15));
    boost::asio::async_read_until(socket_,
        boost::asio::dynamic_buffer(input_buffer_), '\0',
        std::bind(&TcpClient::handle_read, this, _1, _2));
}

template<class Send>
void TcpClient<Send>::handle_read(const boost::system::error_code& ec,
    unsigned int n) {
    if (stopped_) {
        return;
    }
    if (ec) {
        utils::fail(ec, "tcp-client read");
        stop();
        send_(error_msg_);
    } else {
        std::string line(input_buffer_.substr(0, n - 1));
        send_(line);
        stop();
    }
}

template<class Send>
void TcpClient<Send>::check_deadline() {
    if (stopped_) {
        return;
    }
    if (deadline_.expiry() <= steady_timer::clock_type::now()) {
        socket_.close();
        deadline_.expires_at(steady_timer::time_point::max());
    }
    deadline_.async_wait(std::bind(&TcpClient::check_deadline, this));
}

} // client
} // webserver
} // pasteslash

#endif // WEBSERVER_TCP_CLIENT_INL
