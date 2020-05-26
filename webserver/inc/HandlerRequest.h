#ifndef WEBSERVER_HANDLER_REQUEST_HPP
#define WEBSERVER_HANDLER_REQUEST_HPP

#include <boost/noncopyable.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <string>

#include "ALClient.h"

namespace beast = boost::beast;
namespace http = beast::http;

// Parses HTTP request and creates HTTP response
template<class Send>
class HandlerRequest : boost::noncopyable {
public:
    HandlerRequest(const Send& callback);

    // Handle HTTP request
    template<class Body, class Allocator>
    void handle(http::request<Body, http::basic_fields<Allocator>>&& req);

private:

    Send send_;
};

#include "HandlerRequest.inl"

#endif // WEBSERVER_HANDLER_REQUEST_HPP
