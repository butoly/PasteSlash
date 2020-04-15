#ifndef WEBSERVER_HTTP_SERVER_HPP
#define WEBSERVER_HTTP_SERVER_HPP

#include <string>
#include <boost/asio.hpp>

#include "server_interface.hpp"
#include "../connection/connection_manager.hpp"
#include "../request/request_handler.hpp"

namespace pasteslash {
namespace webserver {
namespace server {

class HttpServer : public IHttpServer {
public:
    HttpServer(const HttpServer&) = delete;
    HttpServer& operator=(const HttpServer&) = delete;
    ~HttpServer() override = default;
    
    explicit HttpServer(const std::string& address, const std::string& port);
    
    /// Run the server's io_context loop.
    void run() override;

private:
    /// Perform an asynchronous accept operation.
    void do_accept() override;

    /// Wait for a request to stop the server.
    void do_await_stop() override;

    boost::asio::io_context io_context_;
    boost::asio::signal_set signals_;
    boost::asio::ip::tcp::acceptor acceptor_;
    
    std::unique_ptr<connection::IConnectionManager> connection_manager_;
    request::RequestHandler request_handler_;
};

} // server
} // webserver
} // pasteslash

#endif // WEBSERVER_HTTP_SERVER_HPP