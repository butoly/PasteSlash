#include "../include/DatabaseObject.h"

void DatabaseObject::storeToDB(const dataFormat &fieldValueMap, const std::string& table) {
    try {
        std::string sqlQuery = SqlGenerator::generateAddQuery(table, fieldValueMap);
        Database::getInstance().execPostQuery(sqlQuery);
    }
    catch (const std::exception& exception) {
        std::cout << exception.what() << std::endl;
    }
}

void DatabaseObject::deleteByPK(const dataFormat& pkValueMap,
        const std::string& table) {
    try {
        std::string sqlQuery = SqlGenerator::generateDeleteQuery(table, pkValueMap);
        Database::getInstance().execPostQuery(sqlQuery);
    }
    catch (const std::exception& exception) {
        std::cout << exception.what() << std::endl;
    }
}

void DatabaseObject::updateByPK(const dataFormat &pkValueMap,
        const dataFormat &newParamsMap, const std::string& table) {
    try {
        std::string sqlQuery = SqlGenerator::generateUpdateQuery(table,
                pkValueMap, newParamsMap);
        Database::getInstance().execPostQuery(sqlQuery);
    }
    catch (const std::exception& exception) {
        std::cout << exception.what() << std::endl;
    }
}

std::shared_ptr<dataFormat> DatabaseObject::getByPK(const dataFormat& pkValueMap,
        const std::string& table) {
    queryResultFormat result;
    try {
        std::string sqlQuery = SqlGenerator::generateGetQuery(table, pkValueMap);
        result = Database::getInstance().execGetQuery(sqlQuery);
    }
    catch (const std::exception& exception) {
        std::cout << exception.what() << std::endl;
    }

    if (result.empty())
        return nullptr;
    else
        return std::make_shared<dataFormat>(result.front());
}
