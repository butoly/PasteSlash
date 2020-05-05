#ifndef URL_GEN_KEYGENERATOR_H
#define URL_GEN_KEYGENERATOR_H

#include <string>
#include <queue>

#include "Randomize.h"

#define LENGTH_QUEUE 100 //количество элементов в очередях

class KeyGeneratorClass {
public:
    KeyGeneratorClass();
    ~KeyGeneratorClass();

    void AddKey(std::queue<std::string> *pointer, std::string element);
    std::string ReturnKey(std::queue<std::string> *pointer);
    std::queue<std::string>* ReturnActivePointer();
    void SetPaste(std::string paste);

private:
    std::queue<std::string> queue1;
    std::queue<std::string> queue2;
    std::queue<std::string> *active_queue_pointer;
    std::queue<std::string> *unactive_queue_pointer;
};


#endif //URL_GEN_KEYGENERATOR_H
