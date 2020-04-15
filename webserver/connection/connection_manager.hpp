#ifndef HTTP_CONNECTION_MANAGER_HPP
#define HTTP_CONNECTION_MANAGER_HPP

#include <set>

#include "connection_manager_interface.hpp"
#include "connection.hpp"

namespace pasteslash {
namespace webserver {
namespace connection {

class ConnectionManager : public IConnectionManager {
public:
    ConnectionManager(const ConnectionManager&) = delete;
    ConnectionManager& operator=(const ConnectionManager&) = delete;
    ~ConnectionManager() = default;

    ConnectionManager();

    /// Add the specified connection to the manager and start it.
    void start(ConnectionPtr c);

    /// Stop the specified connection.
    void stop(ConnectionPtr c);

    /// Stop all connections.
    void stop_all() override;

private:
    std::set<ConnectionPtr> connections_;
};

} // connection
} // webserver
} // pasteslash

#endif // HTTP_CONNECTION_MANAGER_HPP
