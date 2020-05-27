#ifndef TEST_FOLDERDBMANAGER_H
#define TEST_FOLDERDBMANAGER_H

#include "DatabaseObject.h"

#define FOLDER_TABLE_NAME "folder"
#define FOLDER_USER_FK_FIELD "user_acc"
#define FOLDER_TITLE_FIELD "title"

class FolderDBManager: public DatabaseObject {
public:
    static void addFolder(const dataFormat& folder);
    static void deleteFolder(const std::string& username, const std::string& title);
    static void updateFolder(const std::string& username, const std::string& title,
            const dataFormat& newParamsMap);
    static std::shared_ptr<dataFormat> getFolder(const std::string& username, const std::string& title);
};

#endif //TEST_FOLDERDBMANAGER_H
