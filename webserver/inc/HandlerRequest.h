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
    // Returns a bad request response
    http::response<http::string_body> get_bad_request(
        beast::string_view why);
    
    // Returns a not found response
    http::response<http::string_body> get_not_found(
        beast::string_view target);
    
    // Returns a server error response
    http::response<http::string_body> get_server_error(
        beast::string_view what);
    
    // Returns ok response
    http::response<http::string_body> get_ok(
        std::string body);
    
    string handle_get_login(AppLayerClient& al_client,
        const string& body, string& reply);
    
    string handle_get_hashes(AppLayerClient& al_client,
        const string& body, const string& nickname, string& reply);
    
    string handle_get_paste(AppLayerClient& al_client,
        const string& body, const string& hash, string& paste);
    
    string handle_post_paste(AppLayerClient& al_client,
        const string& body, string& hash);
    
    string handle_post_register(AppLayerClient& al_client,
        const string& body, string& token);
    
    string handle_delete_code(AppLayerClient& al_client,
        const string& body, const string& hash, string& error);

    const string parse_error = "Illegal request-arguments";
    Send send_;
};

#include "HandlerRequest.inl"

#endif // WEBSERVER_HANDLER_REQUEST_HPP
