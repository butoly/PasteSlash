#ifndef HTTP_CONNECTION_MANAGER_INTERFACE_HPP
#define HTTP_CONNECTION_MANAGER_INTERFACE_HPP

#include <boost/noncopyable.hpp>

#include "connection.hpp"

namespace pasteslash {
namespace webserver {
namespace connection {

class IConnectionManager : boost::noncopyable {
public:
    IConnectionManager(const IConnectionManager&) = delete;
    IConnectionManager& operator=(const IConnectionManager&) = delete;
    virtual ~IConnectionManager() = default;

    virtual void stop_all() = 0;
};

} // connection
} // webserver
} // pasteslash

#endif // HTTP_CONNECTION_MANAGER_INTERFACE_HPP
