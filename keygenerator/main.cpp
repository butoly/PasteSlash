#include "inc/Randomize.h"
#include "inc/KeyGenerator.h"
#include "inc/Session.h"
#include "inc/Server.h"
//#include "../database/include/Database.h"

int main() {
    //Database::getInstance();
    auto const address = boost::asio::ip::address::from_string("127.0.0.1");
    auto *server = new ServerClass(address, 3002);
    server->run();
    return 0;
}