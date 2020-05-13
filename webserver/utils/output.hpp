#ifndef WEBSERVER_OUTPUT_HPP
#define WEBSERVER_OUTPUT_HPP

#include <boost/beast/core.hpp>

namespace beast = boost::beast;

namespace pasteslash {
namespace webserver {
namespace utils {

void fail(beast::error_code ec, char const* what);

} // utils
} // webserver
} // pasteslash

#endif // WEBSERVER_OUTPUT_HPP
