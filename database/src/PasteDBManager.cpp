#include "../include/PasteDBManager.h"

#define PASTE_HASH_FIELD_NAME "hash"
#define PASTE_EXP_TIME_FIELD_NAME "exp_time"

conditionMapFormat createHashConditionMap(const std::string& hash) {
    conditionMapFormat map = {{PASTE_HASH_FIELD_NAME, SignValue("=", hash)}};
    return map;
}

void PasteDBManager::addPaste(const dataFormat &paste) {
    storeToDB(paste, PASTE_TABLE_NAME);
}

conditionMapFormat createGetConitionMap(const std::string& hash) {
    conditionMapFormat map = {{PASTE_HASH_FIELD_NAME, SignValue("=", hash)},
                              {PASTE_EXP_TIME_FIELD_NAME, SignValue(">", "now()")}};
    return map;
}

std::shared_ptr<dataFormat> PasteDBManager::getPaste(const std::string& hash) {
    conditionMapFormat pkValueMap = createHashConditionMap(hash);
    return getByPK(pkValueMap, PASTE_TABLE_NAME);
}

void PasteDBManager::deletePaste(const std::string& hash) {
    conditionMapFormat pkValueMap = createHashConditionMap(hash);
    deleteByPK(pkValueMap, PASTE_TABLE_NAME);
}

void PasteDBManager::updatePaste(const std::string &hash, const dataFormat& newParamsMap) {
    conditionMapFormat pkValueMap = createHashConditionMap(hash);
    updateByPK(pkValueMap, newParamsMap, PASTE_TABLE_NAME);
}

bool PasteDBManager::checkHash(const std::string& hash) {
    queryResultFormat result;
    try {
        conditionMapFormat conditionMap = createHashConditionMap(hash);
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
        conditionMapFormat map = {{PASTE_EXP_TIME_FIELD_NAME, SignValue(">", time)}};
        std::string sqlQuery = SqlGenerator::generateDeleteQuery(PASTE_TABLE_NAME,
                map);
        Database::getInstance().execPostQuery(sqlQuery);
    }
    catch (const std::exception& exception) {
        std::cout << exception.what() << std::endl;
    }
}

