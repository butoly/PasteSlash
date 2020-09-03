#include "../inc/KeyValidation.h"

KeyValidationClass::KeyValidationClass() {

}

KeyValidationClass::~KeyValidationClass() {

}

bool KeyValidationClass::isValidKey(const std::string &key) {
    return PasteDBManager::checkHash(key);
}
