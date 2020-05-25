#include "../inc/KeyValidation.h"
#include "../../database/include/PasteDBManager.h"

KeyValidationClass::KeyValidationClass() {

}

KeyValidationClass::~KeyValidationClass() {

}

bool KeyValidationClass::isValidKey(const std::string &key) {
    return PasteDBManager::checkHash(key);
}
