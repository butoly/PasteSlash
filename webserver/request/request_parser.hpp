#ifndef WEBSERVER_REQUEST_PARSER_HPP
#define WEBSERVER_REQUEST_PARSER_HPP

#include "request.hpp"

namespace pasteslash {
namespace webserver {
namespace request {

class RequestParser {
public:
    RequestParser();

    enum ResultType { good, bad, indeterminate };

    template <class InputIterator>
    ResultType parse(Request& req, InputIterator begin, InputIterator end);

private:
    /// Reset current state
    void reset_state();

    /// Handle the next character of input.
    ResultType consume(Request& req, char input);

    /// Check if a byte is an HTTP character.
    static bool is_char(int c);

    /// Check if a byte is an HTTP control character.
    static bool is_ctl(int c);

    /// Check if a byte is defined as an HTTP tspecial character.
    static bool is_tspecial(int c);

    /// Check if a byte is a digit.
    static bool is_digit(int c);

    /// The current state of the parser.
    enum State {
        method_start,
        method,
        uri,
        http_version_h,
        http_version_t_1,
        http_version_t_2,
        http_version_p,
        http_version_slash,
        http_version_major_start,
        http_version_major,
        http_version_minor_start,
        http_version_minor,
        expecting_newline_1,
        header_line_start,
        header_lws,
        header_name,
        space_before_header_value,
        header_value,
        expecting_newline_2,
        expecting_newline_3
    } state_;
};

} // namespace request
} // namespace webserver
} // namespace pasteslash

#endif // WEBSERVER_REQUEST_PARSER_HPP
