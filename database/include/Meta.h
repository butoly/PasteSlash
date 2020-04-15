#ifndef DATABASE_META_H
#define DATABASE_META_H

#include "unordered_set"

struct Meta {
public:
    std::unordered_set<std::string> fields;
    std::string tableName;
};

#endif // DATABASE_META_H
