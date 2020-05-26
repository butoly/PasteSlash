#ifndef URL_GEN_KEYVALIDATION_H
#define URL_GEN_KEYVALIDATION_H

#include <string>

#include "PasteDBManager.h"

class KeyValidationClass {
public:
    KeyValidationClass();
    ~KeyValidationClass();

    //проверка валидности ключа в БД
    bool isValidKey(const std::string &key);
};

#endif //URL_GEN_KEYVALIDATION_H
