#include "DatabaseManager.h"
#include "PasteManager.h"
#include "UserManager.h"
#include "exception"

void DatabaseManager::addPaste(pasteFormat paste) {
    PasteManager pasteManager;
    try {
        pasteManager.addPaste(std::move(paste));
    }
    catch (std::exception) {}
}

void DatabaseManager::deletePaste(std::string hash) {
    PasteManager pasteManager;
    try {
        pasteManager.deletePaste(std::move(hash));
    }
    catch (std::exception) {}
}

pasteFormat DatabaseManager::getPaste(std::string hash) {
    PasteManager pasteManager;
    pasteFormat paste;
    try {
        paste = pasteManager.getPaste(std::move(hash));
    }
    catch (std::exception) {}

    return paste;
}

void DatabaseManager::addUser(userFormat) {}

void DatabaseManager::deleteUser(const std::string username) {}

userFormat DatabaseManager::getUser(std::string username) {}
