#ifndef WEBSERVER_REQUEST_HANDLER_HPP
#define WEBSERVER_REQUEST_HANDLER_HPP

#include "request.hpp"
#include "../reply/reply.hpp"
#include "../client/tcp_client.hpp"
#include "../tools/task.hpp"

namespace pasteslash {
namespace webserver {
namespace request {

class RequestHandler {
public:
    RequestHandler(const RequestHandler&) = delete;
    RequestHandler& operator=(const RequestHandler&) = delete;
    ~RequestHandler() = default;

    /// Form task to tcp_client
    void handle_request(const Request& req, reply::Reply& rep);

private:
    std::unique_ptr<client::ITcpClient> tcp_client_;
};

} // namespace request
} // namespace webserver
} // namespace pasteslash

#endif // WEBSERVER_REQUEST_HANDLER_HPP
