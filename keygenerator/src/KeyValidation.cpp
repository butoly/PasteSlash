#include "../inc/KeyValidation.h"

bool KeyValidationClass::isValidKey(const std::string &key) {
    //return PasteDBManager::checkHash(key);
    return true;
}

KeyValidationClass& KeyValidationClass::getInstance() {
    static KeyValidationClass keyValidator;
    return keyValidator;
}