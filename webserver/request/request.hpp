#ifndef WEBSERVER_REQUEST_HPP
#define WEBSERVER_REQUEST_HPP

#include <string>
#include <vector>

#include "../tools/header.hpp"

namespace pasteslash {
namespace webserver {
namespace request {

/// A request received from a client.
struct Request {
    std::string method;
    std::string uri;
    int http_version_major;
    int http_version_minor;
    std::vector<Header> headers;
};

} // namespace request
} // namespace webserver
} // namespace pasteslash

#endif // WEBSERVER_REQUEST_HPP
