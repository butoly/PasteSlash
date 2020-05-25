#include "inc/Randomize.h"
#include "inc/KeyGenerator.h"
#include "inc/Session.h"
#include "inc/Server.h"

int main() {
    auto const address = boost::asio::ip::address::from_string("127.0.0.1");
    auto *server = new ServerClass(address, 5555);
    server->run();
    return 0;
}