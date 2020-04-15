#ifndef PROJECT_SOCKET_H
#define PROJECT_SOCKET_H

#include <iostream>

class Socket {
private:
    int fd;
public:
    Socket(std::string addr, int port) {}
    ~Socket() { /* if (sd > 0) ::close(sd); */ }

    int getFD() const noexcept {
        return fd;
    }

    void send(const std::string &s) throw (std::exception);
    std::string recv() throw (std::exception);
    void close() { /* ::close(fd); */ }
};


#endif //PROJECT_SOCKET_H
