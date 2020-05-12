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
    static void storeToDB(const dataFormat& fieldValueMap,
            const std::string& table);
    static void updateByPK(const dataFormat& pkValueMap,
            const dataFormat& newParamsMap, const std::string& table);
    static void deleteByPK(const dataFormat& pkValueMap,
            const std::string& table);
    static std::shared_ptr<dataFormat> getByPK(const dataFormat& pkValueMap,
            const std::string& table);
};

#endif //TEST_DATABASEOBJECT_H
