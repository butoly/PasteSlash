#ifndef PROJECT_MODELS_H
#define PROJECT_MODELS_H
#include <iostream>
#include <vector>
#include <unordered_map>

namespace Models {
    struct ReceivedData {
        std::string command;
        std::unordered_map<std::string, std::string> data;
    };

    struct User {
        User(const std::string& n, const std::string& e, const std::string& p) : nickname(n), email(e), password(p) {}

        User(const std::string& n, const std::string& p) : nickname(n), password(p) {}

        ~User() = default;

        std::string nickname;
        std::string email;
        std::string password;
    };

    struct Code {
        Code() = default;
        Code(const std::string& n, const std::string& b) : name(n), body(b) {}

        ~Code() = default;

        std::string hash;
        std::string name;
        std::string body;
    };

    struct Token {
        Token() = default;
        Token(const std::string& v) : value(v) {}
        ~Token() = default;

        std::string value;
    };
}

#endif //PROJECT_MODELS_H
