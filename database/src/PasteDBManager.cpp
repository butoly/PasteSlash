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

bool PasteDBManager::addPaste(const dataFormat& paste) {
    return storeToDB(paste, PASTE_TABLE_NAME);
}

std::tm parsePostgresTime(const std::string& postgresTime) {
    std::tm tm{0};
    tm.tm_year = std::stoi(postgresTime.substr(0, 4));
    tm.tm_mon = std::stoi(postgresTime.substr(6, 7));
    tm.tm_mday = std::stoi(postgresTime.substr(9, 10));
    tm.tm_hour = std::stoi(postgresTime.substr(11, 13));
    tm.tm_min = std::stoi(postgresTime.substr(14, 16));
    return tm;
}

std::tm getNow() {
    std::time_t tt =
            std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm tm{0};
    gmtime_r(&tt, &tm);
    tm.tm_year += 1900;
    tm.tm_mon += 1;
    return tm;
}

bool checkTime(const std::string& postgresTime) {
    std::tm postTm = parsePostgresTime(postgresTime);
    std::tm nowTm = getNow();
    if (postTm.tm_year > nowTm.tm_year)
        return false;
    else if (postTm.tm_year < nowTm.tm_year)
        return true;
    if (postTm.tm_mon > nowTm.tm_mon)
        return false;
    else if (postTm.tm_mon < nowTm.tm_mon)
        return true;
    if (postTm.tm_mday > nowTm.tm_mday)
        return false;
    else if (postTm.tm_mday < nowTm.tm_mday)
        return true;
    if (postTm.tm_hour > nowTm.tm_hour)
        return false;
    else if (postTm.tm_hour < nowTm.tm_hour)
        return true;

    return postTm.tm_min >= nowTm.tm_min;
}

void deleteIfOverdue(const std::string& hash) {
    conditionMapFormat map = {{PASTE_HASH_FIELD, SignValue("=", hash)},
                              {PASTE_EXPTIME_FIELD, SignValue("<", "now()")}};
    PasteDBManager::deletePaste(hash);
}

std::shared_ptr<dataFormat> PasteDBManager::getPaste(const std::string& hash) {
    conditionMapFormat pkValueMap = createHashConditionMap(hash);
    std::shared_ptr<dataFormat> paste = getByPK(pkValueMap, PASTE_TABLE_NAME);
    if (!paste)
        return paste;
    if ((*paste).at(PASTE_EXPTIME_FIELD).empty())
        return paste;

    /*
    if (checkTime((*paste).at(PASTE_EXPTIME_FIELD))) {
        deletePaste(hash);
        return nullptr;
    }
*/
    return paste;
}

bool PasteDBManager::deletePaste(const std::string& hash) {
    if (!checkHash(hash))
        return false;
    conditionMapFormat conditionMap = createHashConditionMap(hash);
    return deleteByPK(conditionMap, PASTE_TABLE_NAME);
}

bool PasteDBManager::updatePaste(const std::string& hash,
                                 const dataFormat& newParamsMap) {
    if (!checkHash(hash))
        return false;
    conditionMapFormat conditionMap = createHashConditionMap(hash);
    return updateByPK(conditionMap, newParamsMap, PASTE_TABLE_NAME);
}

bool PasteDBManager::updateText(const std::string& hash,
                                const std::string& newText) {
    if (!checkHash(hash))
        return false;
    conditionMapFormat conditionMap = createHashConditionMap(hash);
    return updateByPK(conditionMap, {{"text", newText}}, PASTE_TABLE_NAME);
}

bool PasteDBManager::checkHash(const std::string& hash) {
    conditionMapFormat conditionMap = createHashConditionMap(hash);
    std::shared_ptr<dataFormat> result = getPaste(hash);
    return !(result == nullptr);
}

bool PasteDBManager::deleteOverduePastes(const std::string& time) {
    conditionMapFormat map = {{PASTE_EXPTIME_FIELD, SignValue("<", time)}};
    return deleteByPK(map, PASTE_TABLE_NAME);
}

std::vector<std::string> PasteDBManager::getHashList(
        const std::string& nickname) {
    if (nickname.empty()) return std::vector<std::string>();

    std::string id = std::to_string(UserDBManager::getID(nickname));
    if (std::stoi(id) == NO_ID) return std::vector<std::string>();

    conditionMapFormat map = {{PASTE_USER_FIELD, SignValue("=", id)}};
    std::shared_ptr<queryResultFormat> paste =
            getMany(map, PASTE_TABLE_NAME, PASTE_HASH_FIELD);
    std::vector<std::string> result;
    if (paste == nullptr) return result;

    for (auto element : *paste) {
        result.push_back(element.at(PASTE_HASH_FIELD));
    }
    return result;
}

#define MAX_TITLE_SIZE 60
bool PasteDBManager::addPaste(const std::string& text, const std::string& hash,
                              const int id, const std::string& title) {
    dataFormat paste;
    paste[PASTE_TEXT_FIELD] = text;
    paste[PASTE_HASH_FIELD] = hash;
    paste[PASTE_CREATETIME_FIELD] = "now";

    if (id != NO_ID) paste[PASTE_USER_FIELD] = std::to_string(id);

    if (title.size() > MAX_TITLE_SIZE) return false;
    paste[PASTE_TITLE_FIELD] = title;

    return storeToDB(paste, PASTE_TABLE_NAME);
}

// TODO: rename to getPasteAuthorID
int PasteDBManager::getPasteAuthor(const std::string& hash) {
    std::shared_ptr<dataFormat> paste = getPaste(hash);
    if (paste == nullptr) return 0;
    if ((*paste).at(PASTE_USER_FIELD).empty()) return 0;
    return std::stoi((*paste).at(PASTE_USER_FIELD));
}
