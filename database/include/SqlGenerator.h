#ifndef DATABASE_SQLGENERATOR_H
#define DATABASE_SQLGENERATOR_H

#include "string"
#include "dataFormat.h"

class SqlGenerator {
public:
    // fieldValueMap: map like {field_1: value_1, field_2: value_2}
    // Generate query like
    // INSERT INTO intoTableName(field_1, field_2 ...) VALUES (value_1, value_2...)
    static std::string generateAddQuery(const std::string& into,
            const dataFormat& fieldValueMap);

    // Generate query like
    // UPDATE tableName SET field_1 = newValue1, field_2 = newValue2 ...
    // WHERE conditionField_n = conditionValue_n ...
    static std::string generateUpdateQuery(const std::string& tableName,
            const dataFormat& conditionMap, const dataFormat& newValuesMap,
            const std::string& sign="=");

    // Generate query like
    // DELETE FROM tableName WHERE conditionField_1=conditionValue_1...
    static std::string generateDeleteQuery(const std::string& tableName,
            const dataFormat& conditionMap, const std::string& sign="=");

    // Generate query like
    // SELECT * FROM fromTableName WHERE conditionField_1=conditionValue_1...
    static std::string generateGetQuery(const std::string& from,
           const dataFormat& conditionMap, const std::string& fields="*");
};

#endif // DATABASE_SQLGENERATOR_H
