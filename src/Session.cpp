#include "../inc/Session.h"

#include <utility>

SessionClass::SessionClass(ip::tcp::socket socket, std::shared_ptr<KeyGeneratorClass> keyGenerator)
    : socket(std::move(socket)), keyGenerator(std::move(keyGenerator))
    {}

void SessionClass::start() {
    doRead();
}

void SessionClass::doRead() {
    auto self(shared_from_this());
    async_read(socket, readBuffer, transfer_at_least(1),
                            [self](boost::system::error_code ec, std::size_t length)
                            {
                                if (!ec)
                                {
                                    self->onRead();
                                }
                            });
}

void SessionClass::onRead() {
    std::istream tmp(&readBuffer);
    std::string data;
    tmp >> data;
    std::cout << data << std::endl;
    ///////////////////////////////////////
    std::vector<std::string> test_vector;
    for (size_t i = 0; i < 1000; i++) {
        std::this_thread::sleep_for (std::chrono::milliseconds(1));
        test_vector.push_back(keyGenerator->ReturnKey());
        std::cout << i << " " << test_vector[i] << std::endl;
    }
    ///////////////////////////////////////
    std::ostream output(&writeBuffer);
    std::string key = keyGenerator->ReturnKey();
    output << key;
    doWrite();
}

void SessionClass::doWrite() {
    auto self(shared_from_this());
    async_write(socket, writeBuffer,
                             [self](boost::system::error_code ec, std::size_t /*length*/)
                             {
                                 if (!ec)
                                 {
                                     self->onWrite();
                                 }
                             });
    std::cout << "Key: " << &writeBuffer << std::endl;
}

void SessionClass::onWrite() {
    std::cout << "Connection close" << std::endl;
}


