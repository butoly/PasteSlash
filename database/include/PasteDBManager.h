#ifndef TEST_PASTEDBMANAGER_H
#define TEST_PASTEDBMANAGER_H

#include "DatabaseObject.h"
#include <vector>
#define PASTE_TABLE_NAME "paste"

#define SYNTAX_DEF_VALUE "None"
#define EXPOSURE_DEF_VALUE "Public"
#define TITLE_DEF_VALUE "Untitled"
#define EXPTIME_DEV_VALUE "Never"

#define NO_ID -1

class PasteDBManager : public DatabaseObject {
public:
    static bool addPaste(const dataFormat& paste);
    static bool addPaste(const std::string& text, const std::string& hash, const int id=NO_ID,
            const std::string& title="Untitled");
    static std::shared_ptr<dataFormat> getPaste(const std::string& hash);
    static void deletePaste(const std::string& hash);
    static void updatePaste(const std::string& hash, const dataFormat& newParamsMap);

    static bool checkHash(const std::string& hash);
    static int getPasteAuthor(const std::string& hash);
    static std::vector<std::string> getHashList(const std::string& nickname);
    static void deleteOverduePastes(const std::string& time="now()");
};

#endif //TEST_PASTEDBMANAGER_H
