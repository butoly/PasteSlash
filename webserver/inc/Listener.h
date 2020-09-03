#ifndef WEBSERVER_LISTENER_HPP
#define WEBSERVER_LISTENER_HPP

#include <boost/noncopyable.hpp>
#include <memory>

#include "Session.h"
#include "Output.h"

namespace beast = boost::beast;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

// Accepts incoming connections and launches the sessions
class Listener : public std::enable_shared_from_this<Listener>,
    boost::noncopyable {
public:
    Listener(net::io_context& ioc, tcp::endpoint endpoint);

    // Start accepting incoming connections
    void run();

private:
    // Accept connection
    void do_accept();

    // Handle connection
    void on_accept(beast::error_code ec, tcp::socket socket);

    net::io_context& ioc_;
    tcp::acceptor acceptor_;
};

#endif // WEBSERVER_LISTENER_HPP
