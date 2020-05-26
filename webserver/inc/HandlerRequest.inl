#ifndef WEBSERVER_HANDLER_REQUEST_INL
#define WEBSERVER_HANDLER_REQUEST_INL

#include <boost/noncopyable.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>
#include <map>

#include <iostream>

#include "HandlerRequest.h"

namespace beast = boost::beast;
namespace http = beast::http;
using std::string;
using std::vector;

template<class Send>
HandlerRequest<Send>::HandlerRequest(const Send& callback) :
send_(callback) {}

bool parse_args(std::map<string, string>& res_args, string body) {
    // Check for empty body
    if (res_args.size() == 0 && body.size() == 0) {
        return true;
    }

    // Parse all arguments into vector
    vector<string> args;
    boost::split(args, body, boost::is_any_of("&"));
    if (args.size() != res_args.size()) {
        return false;
    }

    // Get values of arguments by arguments keys
    for (int i = 0; i < args.size(); ++i) {
        vector<string> params;
        boost::split(params, args[i], boost::is_any_of("="));
        
        auto it = res_args.find(params[0]);
        if (it != res_args.end()) {
            if (it->second == "") {
                it->second = params[1];
            } else {
                // Given argument is a repeat of other argument
                return false;
            }
        } else {
            // Given argument is wrong for this request
            return false;
        }
    }
    return true;
}

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
    auto const server_error = [&req](beast::string_view what) {
        http::response<http::string_body> res{
            http::status::internal_server_error, req.version()};
        res.set(http::field::content_type, "text/html");
        res.keep_alive(req.keep_alive());
        res.body() = "An error occurred: '" + std::string(what) + "'";
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
        req.method() != http::verb::post &&
        req.method() != http::verb::delete_) {
        return send_(bad_request("Unknown HTTP-method\n"));
    }

    // Request path must be absolute and not contain "..".
    if(req.target().empty() ||
        req.target()[0] != '/' ||
        req.target().find("..") != beast::string_view::npos) {
        return send_(bad_request("Illegal request-target"));
    }

    // Split target
    std::string target = req.target().to_string();
    std::vector<std::string> splitted;
    boost::split(splitted, target, boost::is_any_of("/"));

    std::string body = req.body();
    std::string reply;
    std::string status;
    static AppLayerClient al_client(grpc::CreateChannel(
        "localhost:50051", grpc::InsecureChannelCredentials()));

    // Respond to GET request
    if(req.method() == http::verb::get) {
        if (splitted.size() < 2) {
            return send_(not_found(req.target()));

        } else if (splitted[1] == "login") {

            std::map<string, string> args;
            args.insert(std::make_pair("nickname", ""));
            args.insert(std::make_pair("email", ""));
            args.insert(std::make_pair("password", ""));

            if (!parse_args(args, body)) {
                return send_(bad_request("Illegal request-arguments"));
            }
            string nickname = args.find("nickname")->second;
            string email = args.find("email")->second;
            string password = args.find("password")->second;
            
            string token;
            status = al_client.AuthUser(nickname, email, password, token);
            reply = token;

        } else if (splitted[1] == "register") {

            std::map<string, string> args;
            args.insert(std::make_pair("nickname", ""));
            args.insert(std::make_pair("email", ""));
            args.insert(std::make_pair("password", ""));

            if (!parse_args(args, body)) {
                return send_(bad_request("Illegal request-arguments"));
            }
            string nickname = args.find("nickname")->second;
            string email = args.find("email")->second;
            string password = args.find("password")->second;
            
            string token;
            status = al_client.RegUser(nickname, email, password, token);
            reply = token;

        } else if (splitted[1] == "hash" && splitted.size() == 3) {

            std::map<string, string> args;
            args.insert(std::make_pair("email", ""));
            args.insert(std::make_pair("password", ""));

            if (!parse_args(args, body)) {
                return send_(bad_request("Illegal request-arguments"));
            }
            string nickname = splitted[2];
            string email = args.find("email")->second;
            string password = args.find("password")->second;

            vector<string> hashes;
            status = al_client.GetAllHashes(nickname, email, password, hashes);
            for (int i = 0; i < hashes.size(); ++i) {
                reply += hashes[i] + "\n";
            }

        } else if (splitted[1] == "paste" && splitted.size() == 3) {

            std::map<string, string> args;
            if (!parse_args(args, body)) {
                return send_(bad_request("Illegal request-arguments"));
            }
            string hash = splitted[2];
            string name;
            string text;
            status = al_client.GetCode(hash, name, text);
            reply = name + "\n\n" + text;

        } else {
            return send_(not_found(req.target()));
        }
    }

    // Respond to POST request
    if(req.method() == http::verb::post) {
        if (splitted.size() < 2) {
            return send_(not_found(req.target()));
        } else if (splitted[1] == "paste" && splitted.size() == 2) {
            
            std::map<string, string> args;
            args.insert(std::make_pair("name", ""));
            args.insert(std::make_pair("text", ""));
            args.insert(std::make_pair("token", ""));

            if (!parse_args(args, body)) {
                return send_(bad_request("Illegal request-arguments"));
            }
            string name = args.find("name")->second;
            string text = args.find("text")->second;
            string token = args.find("token")->second;

            string hash;
            status = al_client.StoreCode(name, text, token, hash);
            reply = hash;
        } else {
            return send_(not_found(req.target()));
        }
    }

    if(req.method() == http::verb::delete_) {
        if (splitted.size() < 2) {
            return send_(not_found(req.target()));
        } else if (splitted[1] == "delete" && splitted.size() == 3) {

            std::map<string, string> args;
            if (!parse_args(args, body)) {
                return send_(bad_request("Illegal request-arguments"));
            }

            string hash = splitted[2];
            string error;
            status = al_client.DeleteCode(hash, error);
            reply = error;

        } else {
            return send_(not_found(req.target()));
        }
    }

    if (status == al_client.positive_reply) {
        return send_(ok(reply));
    } else {
        return send_(server_error(status));
    }
}

#endif // WEBSERVER_HANDLER_REQUEST_INL
