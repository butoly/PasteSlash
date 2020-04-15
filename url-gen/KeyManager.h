#ifndef URL_GEN_KEYMANAGER_H
#define URL_GEN_KEYMANAGER_H

#include <string>

class KeyManager {
public:
    KeyManager();
    ~KeyManager();
    bool CheckValidationKey(std::string key);
};

#endif //URL_GEN_KEYMANAGER_H
