#include "../include/PasteDBManager.h"
#include "../include/UserDBManager.h"
#include "chrono"
#include "iomanip"

#define PASTE_HASH_FIELD "hash"
#define PASTE_TEXT_FIELD "text"
#define PASTE_CREATETIME_FIELD "create_time"
#define PASTE_SYNTAX_FIELD "syntax"
#define PASTE_EXPTIME_FIELD "exp_time"
#define PASTE_USER_FIELD "user_acc"

conditionMapFormat createHashConditionMap(const std::string& hash) {
    conditionMapFormat map = {{PASTE_HASH_FIELD, SignValue("=", hash)}};
    return map;
}

void PasteDBManager::addPaste(const dataFormat &paste) {
    storeToDB(paste, PASTE_TABLE_NAME);
}

conditionMapFormat createGetConditionMap(const std::string& hash) {
    conditionMapFormat map = {{PASTE_HASH_FIELD, SignValue("=", hash)},
                              {PASTE_EXPTIME_FIELD, SignValue(">", "now()")}};
    return map;
}

std::shared_ptr<dataFormat> PasteDBManager::getPaste(const std::string& hash) {
    conditionMapFormat pkValueMap = createGetConditionMap(hash);
    std::shared_ptr<dataFormat> paste = getByPK(pkValueMap, PASTE_TABLE_NAME);

    //std::shared_ptr<queryResultFormat> pastes = getMany(pkValueMap, PASTE_TABLE_NAME);
    //return std::make_shared<dataFormat>(pastes->front());

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
    conditionMapFormat map = {{PASTE_EXPTIME_FIELD, SignValue("<", time)}};
    deleteByPK(map, PASTE_TABLE_NAME);
}

std::vector<std::string> PasteDBManager::getHashList(const std::string &nickname) {
    std::string id = std::to_string(UserDBManager::getID(nickname));
    conditionMapFormat map = {{PASTE_USER_FIELD, SignValue("=", id)}};
    std::shared_ptr<queryResultFormat> paste = getMany(map, PASTE_TABLE_NAME, PASTE_HASH_FIELD);
    std::vector<std::string> result;
    if (paste == nullptr)
        return result;

    for (auto element: *paste) {
        result.push_back(element.at(PASTE_HASH_FIELD));
    }
    return result;
}

bool PasteDBManager::addPaste(const std::string &text, const std::string &hash,
        const std::string &nickname, const std::string& syntax, const std::string &exposure,
        const std::string &expTime, const std::string& title, const std::string &folder) {
    //TODO: expand for all fields
    dataFormat paste;
    paste[PASTE_TEXT_FIELD] = text;
    paste[PASTE_HASH_FIELD] = hash;
    if (!nickname.empty())
        paste[PASTE_USER_FIELD] = std::to_string(UserDBManager::getID(nickname));
    paste[PASTE_CREATETIME_FIELD] = "now";

    return storeToDB(paste, PASTE_TABLE_NAME);
}