#include <thread>
#include <vector>

#include "http_server.hpp"
#include "../listener/listener.hpp"

namespace net = boost::asio;
using Listener = pasteslash::webserver::listener::Listener;

namespace pasteslash {
namespace webserver {
namespace server {

HttpServer::HttpServer(std::string address, std::string port, int threads) :
threads_(threads),
ioc_(net::io_context(threads)) {
    const auto adrs = net::ip::make_address(address);
    const unsigned short prt = static_cast<unsigned short>(std::atoi(port.c_str()));

    // Create and launch a listening port
    std::make_shared<Listener>(ioc_, tcp::endpoint{adrs, prt})->run();
}

void HttpServer::run() {
    std::vector<std::thread> v;
    v.reserve(threads_ - 1);
    for(auto i = threads_ - 1; i > 0; --i) {
        v.emplace_back([this] { ioc_.run(); });
    }
    ioc_.run();
}

} // server
} // webserver
} // pasteslash
