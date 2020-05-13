#ifndef WEBSERVER_HANDLER_REQUEST_INL
#define WEBSERVER_HANDLER_REQUEST_INL

#include <boost/noncopyable.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>

#include "handler_request.hpp"
#include "../tcp_client/tcp_client.hpp"

namespace beast = boost::beast;
namespace http = beast::http;

namespace pasteslash {
namespace webserver {
namespace request {

template<class Send>
HandlerRequest<Send>::HandlerRequest(const Send& callback) :
send_(callback),
lambda_(*this) {}

template<class Send>
template<class Body, class Allocator>
void HandlerRequest<Send>::handle(http::request<Body,
    http::basic_fields<Allocator>>&& req) {
    // Returns a bad request response
    auto const bad_request = [&req](beast::string_view why) {
        http::response<http::string_body> res{
            http::status::bad_request, req.version()};
        res.set(http::field::content_type, "text/html");
        res.keep_alive(req.keep_alive());
        res.body() = std::string(why);
        res.prepare_payload();
        return res;
    };

    // Returns a not found response
    auto const not_found = [&req](beast::string_view target) {
        http::response<http::string_body> res{
            http::status::not_found, req.version()};
        res.set(http::field::content_type, "text/html");
        res.keep_alive(req.keep_alive());
        res.body() = "The resource '" + std::string(target) + "' was not found.";
        res.prepare_payload();
        return res;
    };

    // Returns a server error response
    auto const server_error = [&req]() {
        http::response<http::empty_body> res{
            http::status::internal_server_error, req.version()};
        res.set(http::field::content_type, "text/html");
        res.keep_alive(req.keep_alive());
        res.prepare_payload();
        return res;
    };

    // Returns ok response
    auto const ok = [&req](std::string body) {
        http::response<http::string_body> res{http::status::ok, req.version()};
        res.set(http::field::content_type, "text/html");
        res.keep_alive(req.keep_alive());
        res.body() = body;
        res.prepare_payload();
        return res;
    };

    // Make sure we can handle the method
    if(req.method() != http::verb::get &&
        req.method() != http::verb::post) {
        return send_(bad_request("Unknown HTTP-method\n"));
    }

    // Request path must be absolute and not contain "..".
    if(req.target().empty() ||
        req.target()[0] != '/' ||
        req.target().find("..") != beast::string_view::npos) {
        return send_(bad_request("Illegal request-target"));
    }

    std::string command;
    std::string body = req.body();

    // Split target
    std::string target = req.target().to_string();
    std::vector<std::string> splitted;
    boost::split(splitted, target, boost::is_any_of("/"));

    // Respond to GET request
    if(req.method() == http::verb::get) {
        if (splitted.size() < 2) {
            return send_(not_found(req.target()));
        } else if (splitted[1] == "login") {
            command = "\"login\"";
        } else if (splitted[1] == "register") {
            command = "\"register\"";
        } else if (splitted[1] == "logout") {
            command = "\"logout\"";
        } else if (splitted[1] == "paste" && splitted.size() == 3) {
            command = "\"getPaste\"";
            body = "{\"paste\":\"" + splitted[2] + "\"," +
                body.substr(1, body.size());
        } else {
            return send_(not_found(req.target()));
        }
    }

    // Respond to POST request
    if(req.method() == http::verb::post) {
        if (splitted.size() < 2) {
            return send_(not_found(req.target()));
        } else if (splitted[1] == "paste" && splitted.size() == 2) {
            command = "\"paste\"";
        } else {
            return send_(not_found(req.target()));
        }
    }

    std::string task = "{\"command\":" + command + ",\"body\":" + body + "}";
    send_task(task);
    if (res_body_ == "Server error") {
        return send_(server_error());
    }
    return send_(ok(res_body_));
}

template<class Send>
void HandlerRequest<Send>::send_task(std::string task) {
    boost::asio::io_context io_context;
    auto client = std::make_shared<client::TcpClient<SendLambda>>(
        io_context, lambda_, task);
    client->start();
    io_context.run();
}

template<class Send>
HandlerRequest<Send>::SendLambda::SendLambda(HandlerRequest& self) :
self_(self) {}

template<class Send>
void HandlerRequest<Send>::SendLambda::operator()(const std::string& response)
    const {
    self_.res_body_ = response;
}

} // request
} // webserver
} // pasteslash

#endif // WEBSERVER_HANDLER_REQUEST_INL
