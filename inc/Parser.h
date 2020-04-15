#ifndef PROJECT_PARSER_H
#define PROJECT_PARSER_H

#include <iostream>
#include <vector>
#include <unordered_map>


class Parser {
public:
    Parser() = default;
    ~Parser() = default;

    std::unordered_map<std::string, std::string> parse(std::string& data);
};

#endif //PROJECT_PARSER_H
