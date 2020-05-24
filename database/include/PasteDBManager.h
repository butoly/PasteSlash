#ifndef TEST_PASTEDBMANAGER_H
#define TEST_PASTEDBMANAGER_H

#include "DatabaseObject.h"
#include <vector>
#define PASTE_TABLE_NAME "paste"

class PasteDBManager : public DatabaseObject {
public:
    static void addPaste(const dataFormat& paste);
    static std::shared_ptr<dataFormat> getPaste(const std::string& hash);
    static void deletePaste(const std::string& hash);
    static void updatePaste(const std::string& hash, const dataFormat& newParamsMap);

    static bool checkHash(const std::string& hash);
    static std::vector<std::string> getHashList(const std::string& nickname);
    static void deleteOverduePastes(const std::string& time="now()");
};

#endif //TEST_PASTEDBMANAGER_H
