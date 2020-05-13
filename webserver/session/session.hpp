#ifndef WEBSERVER_SESSION_HPP
#define WEBSERVER_SESSION_HPP

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <memory>

#include "session_interface.hpp"
#include "../request/handler_request.hpp"

namespace beast = boost::beast;
namespace http = beast::http;
using tcp = boost::asio::ip::tcp;

namespace pasteslash {
namespace webserver {
namespace session {

// Handles an HTTP server connection
class Session : public ISession, public std::enable_shared_from_this<Session> {
public:
    Session(tcp::socket&& socket);

    Session(const Session&) = delete;
    Session& operator=(const Session&) = delete;
    ~Session() = default;

    // Start the asynchronous reading
    void run() override;

    // Read request
    void do_read() override;

    // Handle reading
    void on_read(beast::error_code ec, std::size_t bytes_transferred) override;

    // Handle writing
    void on_write(bool close, beast::error_code ec,
        std::size_t bytes_transferred);

    // Close connection
    void do_close();

private:
    // Write response
    struct SendLambda {
        Session& self_;

        explicit SendLambda(Session& self);

        template<bool isRequest, class Body, class Fields>
        void operator()(http::message<isRequest, Body, Fields>&& msg) const;
    };

    beast::tcp_stream stream_;
    beast::flat_buffer buffer_;
    http::request<http::string_body> req_;
    std::shared_ptr<void> res_;
    SendLambda lambda_;
};

} // session
} // webserver
} // pasteslash

#endif // WEBSERVER_SESSION_HPP
