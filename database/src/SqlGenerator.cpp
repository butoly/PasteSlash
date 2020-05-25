#include "../include/SqlGenerator.h"

std::string stringWithQuotes(const std::string& string) {
    return "'" + string + "'";
}

std::string SqlGenerator::generateAddQuery(const std::string& into,
        const dataFormat& fieldValueMap) {
    std::string sqlQuery = "INSERT INTO " + into + "(";

    for (auto & field : fieldValueMap)
        sqlQuery += field.first + ", ";

    sqlQuery = sqlQuery.substr(0, sqlQuery.size() - 2);
    sqlQuery += ") VALUES (";

    for (auto &value : fieldValueMap)
        sqlQuery += stringWithQuotes(value.second) + ", ";

    sqlQuery = sqlQuery.substr(0, sqlQuery.size() - 2);
    sqlQuery += ");";

    return sqlQuery;
}

std::string SqlGenerator::generateGetQuery(const std::string& from,
        const conditionMapFormat& conditionMap, const std::string& fields) {
    std::string sqlQuery = "SELECT " + fields + " FROM " + from +
                           " WHERE ";

    for (const auto& i: conditionMap)
        sqlQuery += i.first + " " + i.second.getString() + " AND ";

    sqlQuery = sqlQuery.substr(0, sqlQuery.size() - 5);
    sqlQuery += ";";

    return sqlQuery;
}

std::string SqlGenerator::generateDeleteQuery(const std::string& tableName,
        const conditionMapFormat& conditionMap) {
    std::string sqlQuery = "DELETE FROM " + tableName +
                           " WHERE ";

    for (const auto& i: conditionMap)
        sqlQuery += i.first + i.second.getString() + " AND ";

    sqlQuery = sqlQuery.substr(0, sqlQuery.size() - 5);
    sqlQuery += ";";

    return sqlQuery;
}

std::string SqlGenerator::generateUpdateQuery(const std::string& tableName,
        const conditionMapFormat& conditionMap, const dataFormat& newValuesMap) {
    std::string sqlQuery = "UPDATE " + tableName + " SET ";

    for (const auto& i: newValuesMap)
        sqlQuery += i.first + "=" + stringWithQuotes(i.second) + ", ";
    sqlQuery = sqlQuery.substr(0, sqlQuery.size() - 2);

    sqlQuery += " WHERE ";
    for (const auto& i: conditionMap)
        sqlQuery += i.first + i.second.getString() + " AND ";

    sqlQuery = sqlQuery.substr(0, sqlQuery.size() - 5);
    sqlQuery += ";";

    return sqlQuery;
}
