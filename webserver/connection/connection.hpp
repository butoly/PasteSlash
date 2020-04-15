#ifndef WEBSERVER_CONNECTION_HPP
#define WEBSERVER_CONNECTION_HPP

#include <array>
#include <memory>
#include <boost/asio.hpp>

#include "../request/request_handler.hpp"
#include "../request/request_parser.hpp"

namespace pasteslash {
namespace webserver {
namespace connection {

class ConnectionManager;

class Connection : public std::enable_shared_from_this<Connection> {
public:
    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;

    explicit Connection(boost::asio::ip::tcp::socket socket,
        ConnectionManager& manager, request::RequestHandler& handler,
        request::RequestParser& parser);

    /// Start the first asynchronous operation for the connection.
    void start();

    /// Stop all asynchronous operations associated with the connection.
    void stop();

private:
    /// Perform an asynchronous read operation.
    void do_read();

    /// Perform an asynchronous write operation.
    void do_write();

    boost::asio::ip::tcp::socket socket_;
    std::array<char, 8192> buffer_;

    ConnectionManager& connection_manager_;
    request::RequestHandler& request_handler_;
    request::RequestParser& request_parser_;
    request::Request request_;
    reply::Reply reply_;
};

typedef std::shared_ptr<Connection> ConnectionPtr;

} // connection
} // webserver
} // pasteslash

#endif // WEBSERVER_CONNECTION_HPP