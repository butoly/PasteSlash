#ifndef WEBSERVER_HANDLER_REQUEST_INL
#define WEBSERVER_HANDLER_REQUEST_INL

#include <boost/noncopyable.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>
#include <map>
#include <fstream>

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
http::response<http::string_body> HandlerRequest<Send>::get_bad_request(
    beast::string_view why) {
    http::response<http::string_body> res{
        http::status::bad_request, 11};
    res.set(http::field::content_type, "text/html");
    res.body() = std::string(why);
    res.prepare_payload();
    return res;
}

template<class Send>
http::response<http::string_body> HandlerRequest<Send>::get_not_found(
    beast::string_view target) {
    http::response<http::string_body> res{
        http::status::not_found, 11};
    res.set(http::field::content_type, "text/html");
    res.body() = "The resource '" + std::string(target) + "' was not found.";
    res.prepare_payload();
    return res;
}

template<class Send>
http::response<http::string_body> HandlerRequest<Send>::get_server_error(
    beast::string_view what) {
    http::response<http::string_body> res{
        http::status::internal_server_error, 11};
    res.set(http::field::content_type, "text/html");
    res.body() = "An error occurred: '" + std::string(what) + "'";
    res.prepare_payload();
    return res;
}

template<class Send>
http::response<http::string_body> HandlerRequest<Send>::get_ok(
    std::string body) {
    http::response<http::string_body> res{http::status::ok, 11};
    res.set(http::field::content_type, "text/html");
    res.body() = body;
    res.prepare_payload();
    return res;
}

template<class Send>
string HandlerRequest<Send>::handle_get_login(AppLayerClient& al_client,
    const string& body, string& token) {
    std::map<string, string> args;
    args.insert(std::make_pair("nickname", ""));
    args.insert(std::make_pair("email", ""));
    args.insert(std::make_pair("password", ""));

    if (!parse_args(args, body)) {
        return parse_error;
    }
    string nickname = args.find("nickname")->second;
    string email = args.find("email")->second;
    string password = args.find("password")->second;
    
    return al_client.AuthUser(nickname, email, password, token);
}

template<class Send>
string HandlerRequest<Send>::handle_get_hashes(AppLayerClient& al_client,
    const string& body, const string& nickname, string& reply) {
    std::map<string, string> args;
    args.insert(std::make_pair("token", ""));
    if (!parse_args(args, body)) {
        return parse_error;
    }
    string token = args.find("token")->second;

    vector<string> hashes;
    string status = al_client.GetAllHashes(nickname, token, hashes);
    for (int i = 0; i < hashes.size(); ++i) {
        reply += hashes[i] + "\n";
    }
    return status;
}

template<class Send>
string HandlerRequest<Send>::handle_get_paste(AppLayerClient& al_client,
    const string& body, const string& hash, string& paste) {
    std::map<string, string> args;
    if (!parse_args(args, body)) {
        return parse_error;
    }
    string name;
    string text;
    string status = al_client.GetCode(hash, name, text);
    paste = name + "\n\n" + text;
    return status;
}

template<class Send>
string HandlerRequest<Send>::handle_post_paste(AppLayerClient& al_client,
    const string& body, string& hash) {
    std::map<string, string> args;
    args.insert(std::make_pair("name", ""));
    args.insert(std::make_pair("text", ""));
    args.insert(std::make_pair("token", ""));

    if (!parse_args(args, body)) {
        return parse_error;
    }
    string name = args.find("name")->second;
    string text = args.find("text")->second;
    string token = args.find("token")->second;
    
    // Check given parametr for file
    std::ifstream pos_file(text);
    if (pos_file.is_open()) {
        string str;
        text = "";
        while (std::getline(pos_file, str)) {
            text += str + "\n";
        }
    }

    return al_client.StoreCode(name, text, token, hash);
}

template<class Send>
string HandlerRequest<Send>::handle_post_register(AppLayerClient& al_client,
    const string& body, string& token) {
    std::map<string, string> args;
    args.insert(std::make_pair("nickname", ""));
    args.insert(std::make_pair("email", ""));
    args.insert(std::make_pair("password", ""));

    if (!parse_args(args, body)) {
        return parse_error;
    }
    string nickname = args.find("nickname")->second;
    string email = args.find("email")->second;
    string password = args.find("password")->second;
    
    return al_client.RegUser(nickname, email, password, token);
}

template<class Send>
string HandlerRequest<Send>::handle_delete_code(AppLayerClient& al_client,
    const string& body, const string& hash, string& error) {
    std::map<string, string> args;
    args.insert(std::make_pair("token", ""));
    if (!parse_args(args, body)) {
        return parse_error;
    }
    string token = args.find("token")->second;

    return al_client.DeleteCode(hash, token, error);
}

template<class Send>
template<class Body, class Allocator>
void HandlerRequest<Send>::handle(http::request<Body,
    http::basic_fields<Allocator>>&& req) {
    // Make sure we can handle the method
    if(req.method() != http::verb::get &&
        req.method() != http::verb::post &&
        req.method() != http::verb::delete_) {
        return send_(get_bad_request("Unknown HTTP-method\n"));
    }

    // Request path must be absolute and not contain "..".
    if(req.target().empty() ||
        req.target()[0] != '/' ||
        req.target().find("..") != beast::string_view::npos) {
        return send_(get_bad_request("Illegal request-target"));
    }

    // Split target
    std::string target = req.target().to_string();
    std::vector<std::string> splitted;
    boost::split(splitted, target, boost::is_any_of("/"));

    std::string body = req.body();
    std::string reply;
    std::string status;
    static AppLayerClient al_client(grpc::CreateChannel(
        "localhost:3001", grpc::InsecureChannelCredentials()));

    // Respond to GET request
    if(req.method() == http::verb::get) {
        if (splitted.size() < 2) {
            return send_(get_not_found(req.target()));
        } else if (splitted[1] == "login") {
            status = handle_get_login(al_client, body, reply);
        } else if (splitted[1] == "hash" && splitted.size() == 3) {
            string nickname = splitted[2];
            status = handle_get_hashes(al_client, body, nickname, reply);
        } else if (splitted[1] == "paste" && splitted.size() == 3) {
            string hash = splitted[2];
            status = handle_get_paste(al_client, body, hash, reply);
        } else {
            return send_(get_not_found(req.target()));
        }
    }

    // Respond to POST request
    if(req.method() == http::verb::post) {
        if (splitted.size() < 2) {
            return send_(get_not_found(req.target()));
        } else if (splitted[1] == "paste" && splitted.size() == 2) {
            status = handle_post_paste(al_client, body, reply);
        } else if (splitted[1] == "register") {
            status = handle_post_register(al_client, body, reply);
        } else {
            return send_(get_not_found(req.target()));
        }
    }

    // Respond to DELETE request
    if(req.method() == http::verb::delete_) {
        if (splitted.size() < 2) {
            return send_(get_not_found(req.target()));
        } else if (splitted[1] == "delete" && splitted.size() == 3) {
            string hash = splitted[2];
            status = handle_delete_code(al_client, body, hash, reply);
        } else {
            return send_(get_not_found(req.target()));
        }
    }

    if (status == al_client.positive_reply) {
        return send_(get_ok(reply));
    } else if (status == parse_error) {
        return send_(get_bad_request(parse_error));
    } else {
        return send_(get_server_error(status));
    }
}

#endif // WEBSERVER_HANDLER_REQUEST_INL
