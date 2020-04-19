#ifndef WEBSERVER_HANDLER_REQUEST_HPP
#define WEBSERVER_HANDLER_REQUEST_HPP

#include <boost/noncopyable.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <string>

#include "../tcp_client/tcp_client.hpp"

namespace beast = boost::beast;
namespace http = beast::http;

namespace pasteslash {
namespace webserver {
namespace request {

class HandlerRequest : boost::noncopyable {
public:
    HandlerRequest()
        : lambda_(*this) {
    }

    template<class Body, class Allocator, class Send>
    void handle_request(http::request<Body,
        http::basic_fields<Allocator>>&& req, Send&& send);

private:
    struct send_lambda {
        HandlerRequest& self_;

        explicit send_lambda(HandlerRequest& self)
            : self_(self) {}

        void operator()(std::string msg) const;
    };

    http::response<http::string_body> bad_request(beast::string_view why);
    http::response<http::string_body> server_error(beast::string_view what);

    send_lambda lambda_;
};

} // request
} // webserver
} // pasteslash

#endif // WEBSERVER_HANDLER_REQUEST_HPP
