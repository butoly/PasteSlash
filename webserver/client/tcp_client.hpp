#ifndef WEBSERVER_TCP_CLIENT_HPP
#define WEBSERVER_TCP_CLIENT_HPP

#include "client_interface.hpp"
#include "../tools/task.hpp"

#include <boost/asio.hpp>

namespace pasteslash {
namespace webserver {
namespace client {

class TcpClient : public ITcpClient {
public:
    void open_connection() override;
    void close_connection() override;
    void add_task(const Task& task);

private:
    void do_connect() override;
    void do_send() override;
    void do_recieve() override;
    void do_close() override;

    // ...
};

} // namespace client
} // namespace webserver
} // namespace pasteslash

#endif // WEBSERVER_TCP_CLIENT_HPP
