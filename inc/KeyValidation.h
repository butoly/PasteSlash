#ifndef URL_GEN_KEYVALIDATION_H
#define URL_GEN_KEYVALIDATION_H

#include <string>

class KeyValidationClass {
public:
    KeyValidationClass();
    ~KeyValidationClass();

    bool IsValidKey(std::string);
};

#endif //URL_GEN_KEYVALIDATION_H
