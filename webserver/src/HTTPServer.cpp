#include <thread>
#include <vector>

#include "HTTPServer.h"
#include "Listener.h"

namespace net = boost::asio;

HTTPServer::HTTPServer(std::string address, std::string port, int threads) :
threads_(threads),
ioc_(net::io_context(threads)) {
    const auto adrs = net::ip::make_address(address);
    const unsigned short prt = static_cast<unsigned short>(std::atoi(port.c_str()));

    // Create and launch a listening port
    std::make_shared<Listener>(ioc_, tcp::endpoint{adrs, prt})->run();
}

void HTTPServer::run() {
    std::vector<std::thread> v;
    v.reserve(threads_ - 1);
    for(auto i = threads_ - 1; i > 0; --i) {
        v.emplace_back([this] { ioc_.run(); });
    }
    ioc_.run();
}
