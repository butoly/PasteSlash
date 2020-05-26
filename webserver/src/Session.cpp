#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio/dispatch.hpp>
#include <memory>

#include "Session.h"
#include "HandlerRequest.h"
#include "Output.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

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
        return fail(ec, "http-server read");
    }
    std::make_shared<HandlerRequest<SendLambda>>(
        lambda_)->handle(std::move(req_));
}

void Session::on_write(bool close, beast::error_code ec,
        std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);
    
    if(ec) {
         return fail(ec, "http-server write");
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

Session::SendLambda::SendLambda(Session& self) :
self_(self) {}

template<bool isRequest, class Body, class Fields>
void Session::SendLambda::operator()(http::message<isRequest,
        Body, Fields>&& msg) const {
    auto sp = std::make_shared<
        http::message<isRequest, Body, Fields>>(std::move(msg));
    self_.res_ = sp;
    http::async_write(self_.stream_, *sp, beast::bind_front_handler(
        &Session::on_write, self_.shared_from_this(), sp->need_eof()));
}
