#ifndef URL_GEN_KEYGENERATOR_H
#define URL_GEN_KEYGENERATOR_H

#include <string>
#include <queue>

#include "Randomize.h"

class KeyGeneratorClass {
public:
    KeyGeneratorClass();
    ~KeyGeneratorClass();

    void AddKey();
    std::string ReturnKey();

private:
    std::queue<std::string> queue1;
    std::queue<std::string> queue2;
    std::queue<std::string> *active_queue_pointer;
    std::queue<std::string> *unactive_queue_pointer;
};


#endif //URL_GEN_KEYGENERATOR_H
