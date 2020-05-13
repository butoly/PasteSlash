#ifndef WEBSERVER_HANDLER_REQUEST_HPP
#define WEBSERVER_HANDLER_REQUEST_HPP

#include <boost/noncopyable.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <string>

namespace beast = boost::beast;
namespace http = beast::http;

namespace pasteslash {
namespace webserver {
namespace request {

// Parses HTTP request and creates HTTP response
template<class Send>
class HandlerRequest : boost::noncopyable {
public:
    HandlerRequest(const Send& callback);

    // Handle HTTP request
    template<class Body, class Allocator>
    void handle(http::request<Body, http::basic_fields<Allocator>>&& req);

private:
    // Send data via tcp client
    void send_task(std::string task);

    // Create response
    struct SendLambda {
        HandlerRequest& self_;

        explicit SendLambda(HandlerRequest& self);

        void operator()(const std::string& response) const;
    };

    Send send_;
    SendLambda lambda_;
    std::string res_body_;
};

} // request
} // webserver
} // pasteslash

#include "handler_request.inl"

#endif // WEBSERVER_HANDLER_REQUEST_HPP
