#include "../include/PasteDBManager.h"

#define PASTE_HASH_FIELD_NAME "hash"
#define PASTE_EXP_TIME_FIELD_NAME "exp_time"

dataFormat createHashConditionMap(const std::string& hash) {
    dataFormat map = {{PASTE_HASH_FIELD_NAME, hash}};
    return map;
}

void PasteDBManager::addPaste(const dataFormat &paste) {
    storeToDB(paste, PASTE_TABLE_NAME);
}

std::shared_ptr<dataFormat> PasteDBManager::getPaste(const std::string& hash) {
    dataFormat pkValueMap = createHashConditionMap(hash);
    return getByPK(pkValueMap, PASTE_TABLE_NAME);
}

void PasteDBManager::deletePaste(const std::string& hash) {
    dataFormat pkValueMap = createHashConditionMap(hash);
    deleteByPK(pkValueMap, PASTE_TABLE_NAME);
}

void PasteDBManager::updatePaste(const std::string &hash, const dataFormat& newParamsMap) {
    dataFormat pkValueMap = createHashConditionMap(hash);
    updateByPK(pkValueMap, newParamsMap, PASTE_TABLE_NAME);
}

bool PasteDBManager::checkHash(const std::string& hash) {
    queryResultFormat result;
    try {
        dataFormat conditionMap = createHashConditionMap(hash);
        std::string sqlQuery = SqlGenerator::generateGetQuery(PASTE_TABLE_NAME,
                conditionMap, PASTE_HASH_FIELD_NAME);
        result = Database::getInstance().execGetQuery(sqlQuery);
    }
    catch (const std::exception& exception) {
        std::cout << exception.what() << std::endl;
    }

    return !result.empty();
}

void PasteDBManager::deleteOverduePastes(const std::string &time) {
    try {
        dataFormat map = {{PASTE_EXP_TIME_FIELD_NAME, time}};
        std::string sqlQuery = SqlGenerator::generateDeleteQuery(PASTE_TABLE_NAME,
                map, "<");
        Database::getInstance().execPostQuery(sqlQuery);
    }
    catch (const std::exception& exception) {
        std::cout << exception.what() << std::endl;
    }
}
