#ifndef WEBSERVER_OUTPUT_HPP
#define WEBSERVER_OUTPUT_HPP

#include <boost/beast/core.hpp>

namespace beast = boost::beast;

void fail(beast::error_code ec, char const* what);

#endif // WEBSERVER_OUTPUT_HPP
