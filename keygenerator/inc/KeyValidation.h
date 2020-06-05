#ifndef URL_GEN_KEYVALIDATION_H
#define URL_GEN_KEYVALIDATION_H

#include <string>

//#include "PasteDBManager.h"

//синглтон
class KeyValidationClass {
private:
    KeyValidationClass() = default;
    ~KeyValidationClass() = default;

    KeyValidationClass(KeyValidationClass const&) = delete;
    KeyValidationClass& operator= (KeyValidationClass const&) = delete;
public:
    static KeyValidationClass& getInstance();
    static bool isValidKey(const std::string &key); //проверка валидности ключа в БД
};

#endif //URL_GEN_KEYVALIDATION_H
