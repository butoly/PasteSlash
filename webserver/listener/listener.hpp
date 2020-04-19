#ifndef WEBSERVER_LISTENER_HPP
#define WEBSERVER_LISTENER_HPP

#include <boost/noncopyable.hpp>
#include <boost/beast/core.hpp>
#include <boost/asio/strand.hpp>
#include <memory>

// #include "../session/session.hpp"

namespace beast = boost::beast;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

namespace pasteslash {
namespace webserver {
namespace listener {

class Listener : boost::noncopyable {
public:
    Listener(net::io_context& ioc, tcp::endpoint endpoint)
        : ioc_(ioc), acceptor_(net::make_strand(ioc)) {
    }

    void run();

private:
    void do_accept();

    void on_accept(beast::error_code ec, tcp::socket socket);

    net::io_context& ioc_;
    tcp::acceptor acceptor_;
};

} // listener
} // webserver
} // pasteslash

#endif // WEBSERVER_LISTENER_HPP
