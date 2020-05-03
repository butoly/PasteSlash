#ifndef PROJECT_MODELS_H
#define PROJECT_MODELS_H
#include <iostream>
#include <vector>
#include <unordered_map>

struct ReceivedData {
    std::string command;
    std::unordered_map<std::string, std::string> data;
};

struct User {
    User(std::string& n, std::string& e, std::string& p) : nickname(n), email(e), password(p) {}
    User(std::string& n, std::string& p) : nickname(n), password(p) {}
    ~User() = default;
    std::string nickname;
    std::string email;
    std::string password;
};

struct Code {

    std::string hash;
    std::string name;
    std::string body;
};

#endif //PROJECT_MODELS_H
