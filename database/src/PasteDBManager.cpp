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

conditionMapFormat createGetConditionMap(const std::string& hash) {
    conditionMapFormat map = {{PASTE_HASH_FIELD_NAME, SignValue("=", hash)},
                              {PASTE_EXP_TIME_FIELD_NAME, SignValue(">", "now()")}};
    return map;
}

std::shared_ptr<dataFormat> PasteDBManager::getPaste(const std::string& hash) {
    conditionMapFormat pkValueMap = createGetConditionMap(hash);
    std::shared_ptr<dataFormat> paste = getByPK(pkValueMap, PASTE_TABLE_NAME);
    if (!paste)
        deletePaste(hash);
    return paste;
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
    conditionMapFormat conditionMap = createHashConditionMap(hash);
    std::shared_ptr<dataFormat> result = getPaste(hash);
    return !(result == nullptr);
}

void PasteDBManager::deleteOverduePastes(const std::string &time) {
    conditionMapFormat map = {{PASTE_EXP_TIME_FIELD_NAME, SignValue("<", time)}};
    deleteByPK(map, PASTE_TABLE_NAME);
}

