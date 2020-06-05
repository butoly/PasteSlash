#include "tcpclient/TCPClient.h"

boost::system::errc::errc_t TCPClient::connect() {
    boost::system::error_code error = error::would_block;

    async_connect(socket, iter, var(error) = boost::lambda::_1);
    do {
        ioc.run_one();
    } while (error == error::would_block);
    //socket.connect(ep, error);

    if (error) {
        std::cout << "client terminated " << error.message() << std::endl;
        return boost::system::errc::not_connected;
    }
    return boost::system::errc::success;
}

std::string TCPClient::send(std::string& msg) {

    boost::system::error_code error;
    write(socket, boost::asio::buffer(msg), error);
    if(error) {
        std::cout << "send failed: " << error.message() << std::endl;
    }

    return receive();
}

std::string TCPClient::receive() {
    streambuf receive_buffer;
    boost::system::error_code error = error::would_block;
    async_read_until(socket, receive_buffer, '\n', var(error) = boost::lambda::_1);
    do {
        ioc.run_one();
    } while (error == error::would_block);

    //read(socket, receive_buffer, transfer_all(), error);
    if (error && error != boost::asio::error::eof) {
        std::cout << "receive failed: " << error.message() << std::endl;
    }
    std::string s( (std::istreambuf_iterator<char>(&receive_buffer)), std::istreambuf_iterator<char>() );
    return s;
}

void TCPClient::checkDeadline() {
    if (timer.expires_at() <= deadline_timer::traits_type::now()) {
        boost::system::error_code error;
        socket.close(error);
        timer.expires_at(boost::posix_time::pos_infin);
    }
    timer.async_wait(boost::bind(&TCPClient::checkDeadline, this));
}