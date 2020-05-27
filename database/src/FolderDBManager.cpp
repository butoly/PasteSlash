#include "../include/FolderDBManager.h"

void FolderDBManager::addFolder(const dataFormat &folder) {
    storeToDB(folder, FOLDER_TABLE_NAME);
}

conditionMapFormat createPKValueMap(const std::string &username,
        const std::string &title) {
    return {{FOLDER_USER_FK_FIELD, SignValue("=", username)},
            {FOLDER_TITLE_FIELD, SignValue("=", title)}};
}

void FolderDBManager::deleteFolder(const std::string &username,
                                   const std::string &title) {
    conditionMapFormat pkValueMap = createPKValueMap(username, title);
    deleteByPK(pkValueMap, FOLDER_TABLE_NAME);
}

void FolderDBManager::updateFolder(const std::string &username,
                                   const std::string &title, const dataFormat &newParamsMap) {
    conditionMapFormat pkValueMap = createPKValueMap(username, title);
    updateByPK(pkValueMap, newParamsMap, FOLDER_TABLE_NAME);
}

std::shared_ptr<dataFormat> FolderDBManager::getFolder(const std::string &username,
                                                       const std::string &title) {
    conditionMapFormat pkValueMap = createPKValueMap(username, title);
    return getByPK(pkValueMap, FOLDER_TABLE_NAME);
}
