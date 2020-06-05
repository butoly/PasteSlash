#include "../include/DatabaseObject.h"

bool DatabaseObject::storeToDB(const dataFormat& fieldValueMap,
                               const std::string& table) {
    bool result = false;
    try {
        std::string sqlQuery = SqlGenerator::generateAddQuery(table, fieldValueMap);
        result = Database::getInstance().execPostQuery(sqlQuery);
    } catch (const std::exception& exception) {
        std::cout << exception.what() << std::endl;
    }

    return result;
}

bool DatabaseObject::deleteByPK(const conditionMapFormat& pkValueMap,
                                const std::string& table) {
    bool result = false;
    try {
        std::string sqlQuery = SqlGenerator::generateDeleteQuery(table, pkValueMap);
        result = Database::getInstance().execPostQuery(sqlQuery);
    } catch (const std::exception& exception) {
        std::cout << exception.what() << std::endl;
    }

    return result;
}

bool DatabaseObject::updateByPK(const conditionMapFormat& conditionMap,
                                const dataFormat& newParamsMap,
                                const std::string& table) {
    bool result;
    try {
        std::string sqlQuery =
                SqlGenerator::generateUpdateQuery(table, conditionMap, newParamsMap);
        result = Database::getInstance().execPostQuery(sqlQuery);
    } catch (const std::exception& exception) {
        std::cout << exception.what() << std::endl;
    }

    return result;
}

std::shared_ptr<queryResultFormat> DatabaseObject::getMany(
        const conditionMapFormat& conditionMap, const std::string& table,
        const std::string& fields) {
    queryResultFormat result;
    try {
        std::string sqlQuery =
                SqlGenerator::generateGetQuery(table, conditionMap, fields);
        result = Database::getInstance().execGetQuery(sqlQuery);
    } catch (const std::exception& exception) {
        std::cout << exception.what() << std::endl;
    }

    if (result.empty())
        return nullptr;
    else
        return std::make_shared<queryResultFormat>(result);
}

std::shared_ptr<dataFormat> DatabaseObject::getByPK(
        const conditionMapFormat& conditionMap, const std::string& table,
        const std::string& fields) {
    queryResultFormat result;
    try {
        std::string sqlQuery =
                SqlGenerator::generateGetQuery(table, conditionMap, fields);
        result = Database::getInstance().execGetQuery(sqlQuery);
    } catch (const std::exception& exception) {
        std::cout << exception.what() << std::endl;
    }

    if (result.empty())
        return nullptr;
    else
        return std::make_shared<dataFormat>(result.front());
}
