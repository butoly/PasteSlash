#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio/dispatch.hpp>
#include <memory>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

#include "session.hpp"
#include "../utils/output.hpp"

namespace pasteslash {
namespace webserver {
namespace session {

Session::Session(tcp::socket&& socket) :
stream_(std::move(socket)),
lambda_(*this) {}

void Session::run() {
    net::dispatch(stream_.get_executor(),
        beast::bind_front_handler(&Session::do_read, shared_from_this()));
}

void Session::do_read() {
    req_ = {};
    stream_.expires_after(std::chrono::seconds(30));
    http::async_read(stream_, buffer_, req_,
        beast::bind_front_handler(&Session::on_read, shared_from_this()));
}

void Session::on_read(beast::error_code ec, std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);
    if(ec == http::error::end_of_stream) {
        return do_close();
    }
    if(ec) {
        return utils::fail(ec, "read");
    }
    // handle(std::move(req_), lambda_);
    // request::func();
    // request::handle(std::move(req_), lambda_);
    // std::make_shared<request::HandlerRequest>()->handle(std::move(req_), lambda_);
    // std::make_shared<session::Session>(std::move(socket))->run();
    // std::make_shared<request::HandlerRequest>()->handle(std::move(req_), lambda_);
    auto a = std::make_shared<request::HandlerRequest>();
    a->handle(std::move(req_), lambda_);
}

void Session::on_write(bool close, beast::error_code ec,
        std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);
    
    if(ec) {
         return utils::fail(ec, "write");
     }
     if(close) {
        return do_close();
    }
    res_ = nullptr;
    do_read();
}

void Session::do_close() {
    beast::error_code ec;
    stream_.socket().shutdown(tcp::socket::shutdown_send, ec);
}

Session::send_lambda::send_lambda(Session& self) :
self_(self) {}
#include <iostream>
template<bool isRequest, class Body, class Fields>
void Session::send_lambda::operator()(http::message<isRequest,
        Body, Fields>&& msg) const {
    std::cout << "skflaksfalks\n";
    auto sp = std::make_shared<
        http::message<isRequest, Body, Fields>>(std::move(msg));
    self_.res_ = sp;
    http::async_write(self_.stream_, *sp, beast::bind_front_handler(
        &Session::on_write, self_.shared_from_this(), sp->need_eof()));
}

} // session
} // webserver
} // pasteslash
