#ifndef PROJECT_APPLICATION_H
#define PROJECT_APPLICATION_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include "TCPClient.h"

class SomeException : public std::exception {
public:
    const char * what() const noexcept override {
        return "exception";
    }
};


class Application {
private:

    Application() = default;

public:
    ~Application() = default;

    static Application& getInstance() {
        static Application app;
        return app;
    }

    void storeCode(std::string& data);
    void regUser();
    void getCode();
    void deleteCode();
    void authUser();
};

#endif //PROJECT_APPLICATION_H
