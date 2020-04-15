#include "KeyManager.h"
#include "KeyGen.h"
#include "Server.h"

int main() {
    Server server = Server();
    RandomKeyGen keyGenerator = RandomKeyGen();
    KeyManager keyManager = KeyManager();

    boost::asio::io_service io_service;
    tcp::acceptor acceptor_(io_service, tcp::endpoint(tcp::v4(), 1234 ));
    tcp::socket socket_(io_service);
    acceptor_.accept(socket_);
    std::string message = server.read_(socket_);
    std::cout << message << std::endl;

    std::string key;
    do {
        key = keyGenerator.getKey();
    } while(!keyManager.CheckValidationKey(key));

    server.send_(socket_, key);

    return 0;
}