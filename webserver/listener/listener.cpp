#include <boost/noncopyable.hpp>
#include <boost/beast/core.hpp>
#include <boost/asio/strand.hpp>
#include <memory>
#include <iostream>

#include "listener.hpp"
#include "../utils/output.hpp"

namespace beast = boost::beast;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

namespace pasteslash {
namespace webserver {
namespace listener {

Listener::Listener(net::io_context& ioc, tcp::endpoint endpoint) :
ioc_(ioc),
acceptor_(net::make_strand(ioc)) {
    beast::error_code ec;

    // Open the acceptor
    acceptor_.open(endpoint.protocol(), ec);
    if(ec) {
        utils::fail(ec, "http-server open");
        return;
    }

    // Allow address reuse
    acceptor_.set_option(net::socket_base::reuse_address(true), ec);
    if(ec) {
        utils::fail(ec, "http-server set_option");
        return;
    }

    // Bind to the server address
    acceptor_.bind(endpoint, ec);
    if(ec) {
        utils::fail(ec, "http-server bind");
        return;
    }

    // Start listening for connections
    acceptor_.listen(net::socket_base::max_listen_connections, ec);
    if(ec) {
        utils::fail(ec, "http-server listen");
        return;
    }
}

void Listener::run() {
    do_accept();
}

void Listener::do_accept() {
    // Connection gets its own strand
    acceptor_.async_accept(net::make_strand(ioc_),
        beast::bind_front_handler(&Listener::on_accept, shared_from_this()));
}

void Listener::on_accept(beast::error_code ec, tcp::socket socket) {
    if (ec) {
        utils::fail(ec, "http-server accept");
    } else {
        std::make_shared<session::Session>(std::move(socket))->run();
    }
    do_accept();
}

} // listener
} // webserver
} // pasteslash
