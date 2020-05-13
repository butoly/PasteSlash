#include "handler_request.hpp"

namespace pasteslash {
namespace webserver {
namespace request {

// / - ?

// /login
// {
//     "command":"login",
//     "body":{"email":"*@*", "password":"*"}
// }

// /register
// {
//     "command":"register",
//     "body":{"email":"*@*", "password":"*"}
// }

// /logout
// {
//     "command":"logout",
//     "body":{}
// }

// /GkAFsR
// {
//     "command":"get_paste",
//     "body":{"code":"GkAFsR"}
// }

// /paste
// {
//     "command":"paste",
//     "body":{"data":"*"}
// }

// template<class Send>
// HandlerRequest<Send>::HandlerRequest(Send& callback) :
// send(callback) {}
    // char* host = "127.0.0.1";
    // char* port = "8000";
// }

// template<class Send>
// http::response<http::string_body> HandlerRequest<Send>::bad_request(
//     beast::string_view why) {
//     // http::response<http::string_body> res{http::status::bad_request, req.version()};
//     // res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
//     // res.set(http::field::content_type, "text/html");
//     // res.keep_alive(req.keep_alive());
//     // res.body() = std::string(why);
//     // res.prepare_payload();
//     // return res;
// }

// template<class Send>
// http::response<http::string_body> HandlerRequest<Send>::server_error(
//     beast::string_view what) {
//     // http::response<http::string_body> res{http::status::not_found, req.version()};
//     // res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
//     // res.set(http::field::content_type, "text/html");
//     // res.keep_alive(req.keep_alive());
//     // res.body() = "The resource '" + std::string(target) + "' was not found.";
//     // res.prepare_payload();
//     // return res;
// }

} // request
} // webserver
} // pasteslash
