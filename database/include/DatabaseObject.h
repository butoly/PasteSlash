#ifndef TEST_DATABASEOBJECT_H
#define TEST_DATABASEOBJECT_H

#include <string>
#include <memory>
#include <unordered_set>

#include "SqlGenerator.h"
#include "Database.h"
#include "dataFormat.h"

class DatabaseObject {
protected:
    static bool storeToDB(const dataFormat& fieldValueMap,
                          const std::string& table);
    static bool updateByPK(const conditionMapFormat& conditionMap,
                           const dataFormat& newParamsMap,
                           const std::string& table);
    static bool deleteByPK(const conditionMapFormat& conditionMap,
                           const std::string& table);
    static std::shared_ptr<dataFormat> getByPK(
            const conditionMapFormat& conditionMap, const std::string& table,
            const std::string& fields = "*");
    static std::shared_ptr<queryResultFormat> getMany(
            const conditionMapFormat& conditionMap, const std::string& table,
            const std::string& fields = "*");
};

#endif  // TEST_DATABASEOBJECT_H
