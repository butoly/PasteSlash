#ifndef WEBSERVER_REPLY_HPP
#define WEBSERVER_REPLY_HPP

#include <string>
#include <vector>

namespace pasteslash {
namespace webserver {
namespace reply {

struct Reply {
    enum StatusType {
        ok = 200,
        created = 201,
        accepted = 202,
        no_content = 204,
        multiple_choices = 300,
        moved_permanently = 301,
        moved_temporarily = 302,
        not_modified = 304,
        bad_request = 400,
        unauthorized = 401,
        forbidden = 403,
        not_found = 404,
        internal_server_error = 500,
        not_implemented = 501,
        bad_gateway = 502,
        service_unavailable = 503
    } status;

    /// Get a reply.
    static Reply get_reply(StatusType status);
};

} // namespace reply
} // namespace webserver
} // namespace pasteslash

#endif // WEBSERVER_REPLY_HPP