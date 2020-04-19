#ifndef WEBSERVER_SESSION_HPP
#define WEBSERVER_SESSION_HPP

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <iostream>
#include <memory>
#include <string>

#include "session_interface.hpp"
#include "../request/handler_request.hpp"

namespace beast = boost::beast;
namespace http = beast::http;
using tcp = boost::asio::ip::tcp;

namespace pasteslash {
namespace webserver {
namespace session {

class Session : public ISession {
public:
    Session(const Session&) = delete;
    Session& operator=(const Session&) = delete;
    ~Session() = default;

    Session(tcp::socket&& socket)
        : stream_(std::move(socket)), lambda_(*this) {
    }

    void run() override;

    void do_read() override;

    void on_read(beast::error_code ec, std::size_t bytes_transferred) override;

    void on_write(bool close, beast::error_code ec,
        std::size_t bytes_transferred);

    void do_close();

private:
    struct send_lambda {
        Session& self_;

        explicit send_lambda(Session& self)
            : self_(self) {}

        template<bool isRequest, class Body, class Fields>
        void operator()(http::message<isRequest, Body, Fields>&& msg) const;
    };

    beast::tcp_stream stream_;
    beast::flat_buffer buffer_;
    http::request<http::string_body> req_;
    std::shared_ptr<void> res_;
    send_lambda lambda_;
};

} // session
} // webserver
} // pasteslash

#endif // WEBSERVER_SESSION_HPP
