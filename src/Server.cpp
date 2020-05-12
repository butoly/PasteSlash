#include "../inc/Server.h"

using namespace boost::asio;

ServerClass::ServerClass(const ip::address& address, unsigned short port)
: endpoint(address, port), service(), acceptor(service, endpoint), socket(service) {
    boost::system::error_code err;
    acceptor.set_option(socket_base::reuse_address(true), err);
    if(err) {
        std::cerr << "err2:" << err.message() << std::endl;
    }
    acceptor.listen(socket_base::max_connections, err);
    if(err) {
        std::cerr << "err3:" << err.message() << std::endl;
    }

    keyGenerator = new KeyGeneratorClass();
}

void ServerClass::accept() {
    acceptor.async_accept(socket, [this](boost::system::error_code err) {
        if(!err) {
            std::cout << "New connection" << std::endl;
            std::make_shared<SessionClass>(std::move(socket), keyGenerator)->start();
        }
        accept();
    });
}

void ServerClass::run() {
    accept();

    std::vector<std::thread> threads;
    for(int i = 0; i < 2; i++) { // TODO количество потоков???
        threads.emplace_back([this](){
            service.run();
        });
    }

    for(auto& thread : threads) {
        thread.join();
    }
}


