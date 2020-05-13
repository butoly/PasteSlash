#include <iostream>

#include "output.hpp"

namespace pasteslash {
namespace webserver {
namespace utils {

void fail(beast::error_code ec, char const* what) {
    std::cerr << what << ": " << ec.message() << "\n";
}

} // utils
} // webserver
} // pasteslash
