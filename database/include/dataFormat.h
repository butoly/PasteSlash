#ifndef DATABASE_DATAFORMAT_H
#define DATABASE_DATAFORMAT_H

#include <unordered_map>
#include <iostream>
#include <vector>
#include <boost/any.hpp>

typedef std::unordered_map<std::string, std::string> dataFormat;
typedef std::vector<dataFormat> queryResultFormat;

#endif //DATABASE_DATAFORMAT_H
