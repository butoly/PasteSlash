#ifndef WEBSERVER_LISTENER_HPP
#define WEBSERVER_LISTENER_HPP

#include <boost/noncopyable.hpp>
#include <memory>

#include "../session/session.hpp"
#include "../utils/output.hpp"

namespace beast = boost::beast;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

namespace pasteslash {
namespace webserver {
namespace listener {

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

} // listener
} // webserver
} // pasteslash

#endif // WEBSERVER_LISTENER_HPP
