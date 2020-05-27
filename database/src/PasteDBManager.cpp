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
#define PASTE_TITLE_FIELD "title"

conditionMapFormat createHashConditionMap(const std::string& hash) {
    conditionMapFormat map = {{PASTE_HASH_FIELD, SignValue("=", hash)}};
    return map;
}

bool PasteDBManager::addPaste(const dataFormat &paste) {
    return storeToDB(paste, PASTE_TABLE_NAME);
}

conditionMapFormat createGetConditionMap(const std::string& hash) {
    conditionMapFormat map = {{PASTE_HASH_FIELD, SignValue("=", hash)},
                              {PASTE_EXPTIME_FIELD, SignValue("IS NOT NULL", "")},
                              {PASTE_EXPTIME_FIELD, SignValue(">", "now()")}};
    return map;
}

std::shared_ptr<dataFormat> PasteDBManager::getPaste(const std::string& hash) {
    conditionMapFormat pkValueMap = createHashConditionMap(hash);
    std::shared_ptr<dataFormat> paste = getByPK(pkValueMap, PASTE_TABLE_NAME);
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
    if (nickname.empty())
        return std::vector<std::string>();

    std::string id = std::to_string(UserDBManager::getID(nickname));
    if (std::stoi(id) == NO_ID)
        return std::vector<std::string>();

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

#define MAX_TITLE_SIZE 60
bool PasteDBManager::addPaste(const std::string &text, const std::string &hash,
        const int id, const std::string& title) {
    dataFormat paste;
    paste[PASTE_TEXT_FIELD] = text;
    paste[PASTE_HASH_FIELD] = hash;
    paste[PASTE_CREATETIME_FIELD] = "now";

    if (id != NO_ID)
        paste[PASTE_USER_FIELD] = std::to_string(id);

    if (title.size() > MAX_TITLE_SIZE)
        return false;
    paste[PASTE_TITLE_FIELD] = title;

    return storeToDB(paste, PASTE_TABLE_NAME);
}

//TODO: rename to getPasteAuthorID
int PasteDBManager::getPasteAuthor(const std::string &hash) {
    std::shared_ptr<dataFormat> paste = getPaste(hash);
    if (paste == nullptr)
        return 0;
    if ((*paste).at(PASTE_USER_FIELD).empty())
        return 0;
    return std::stoi((*paste).at(PASTE_USER_FIELD));
}
