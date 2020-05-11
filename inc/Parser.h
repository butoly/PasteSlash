#ifndef PROJECT_PARSER_H
#define PROJECT_PARSER_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

#include "Models.h"

namespace bpt = boost::property_tree;

class Parser {
    ReceivedData receivedData;

public:
    Parser() = default;
    ~Parser() = default;

    ReceivedData parse(std::string& data);
    std::string prepare(std::string& command, std::string& data);
    std::string parseHash(std::string& data);
};

#endif //PROJECT_PARSER_H
