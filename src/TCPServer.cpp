#include "TCPServer.h"

void TCPServer::start(const char* addr, unsigned short port) {
    // Определяем endpoint
    ip::tcp::endpoint ep(ip::make_address(addr), port);

    boost::system::error_code ec;

    // Открываем сокет
    acceptor.open(ep.protocol(), ec);

    if (ec) {
        return;
    }

    // Позволяем связывать один адресс со множеством сокетов
    acceptor.set_option(boost::asio::socket_base::reuse_address(true), ec);

    if (ec) {
        return;
    }

    // Привязываем сокет к endpoint
    acceptor.bind(ep, ec);

    if (ec) {
        return;
    }

    // Переводим сокет в состояние прослушивания 1024 одновременных соединений
    acceptor.listen(1024, ec);

    if (ec) {
        return;
    }

    // Асинхронно ожидаем соединения
    listen();

    // eventloop с каким-то механизмом опроса сокетов на события

    long number = sysconf(_SC_NPROCESSORS_ONLN);
    std::vector<std::thread> threads;
    for (int i = 0; i < number; ++i) {
        threads.push_back(std::thread(std::bind(&TCPServer::run, this)));
    }

    for (auto& thread : threads) {
        thread.join();
    }
}

void TCPServer::onAccept(std::shared_ptr<Connection> conn, const boost::system::error_code& ec) {
    std::cerr << "+client: "
              << conn->getSocket().remote_endpoint().address().to_string().c_str()
              << std::endl;

    if (!ec) {
        // Создаем инстанс соединения с сокетом воркера и вызываем обработку
        conn->process();
        // Продолжаем слушать соединения
        listen();
        return;
    }

    std::cerr << ec.message() << std::endl;
}

void TCPServer::listen() {
    if (!acceptor.is_open()) {
        return;
    }

    std::shared_ptr<Connection> conn = std::make_shared<Connection>(ioc);

    // Асинхронно принимаем соединения
    acceptor.async_accept(conn->getSocket(), boost::bind(&TCPServer::onAccept, this, conn,
                                                         boost::asio::placeholders::error));
}
