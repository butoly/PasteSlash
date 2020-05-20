#ifndef DATABASE_DATAFORMAT_H
#define DATABASE_DATAFORMAT_H

#include <unordered_map>
#include <iostream>
#include <vector>
#include <boost/any.hpp>

typedef std::unordered_map<std::string, std::string> dataFormat;
typedef std::vector<dataFormat> queryResultFormat;

struct SignValue {
    SignValue(std::string sign_, std::string value_):
    sign(sign_),
    value(value_)
    {}

    std::string sign;
    std::string value;

    [[nodiscard]] std::string getString() const {
        return sign + "'" + value + "'";
    }
};

typedef std::unordered_map<std::string, SignValue> conditionMapFormat;
#endif //DATABASE_DATAFORMAT_H
