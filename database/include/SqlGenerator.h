#ifndef DATABASE_SQLGENERATOR_H
#define DATABASE_SQLGENERATOR_H

#include "string"
#include "DatabaseObject.h"
#include "unordered_set"
#include "dataFormat.h"
#include "Meta.h"

class SqlGenerator {
public:
    std::string generateAddQuery(dataFormat, Meta);
    std::string generateDeleteQuery(dataFormat , Meta);
    std::string generateGetQuery(dataFormat, Meta);
};

#endif // DATABASE_SQLGENERATOR_H
