#include <queue>
#include "../inc/KeyGenerator.h"

KeyGeneratorClass :: KeyGeneratorClass() {

    RandomizeClass *randomize = new RandomizeClass();
    active_queue_pointer = &queue1;
    unactive_queue_pointer = &queue2;

    for(size_t i = 0; i < LENGTH_QUEUE; i++) {
        std::string tmp_key = randomize->ReturnRandomString();
        AddKey(active_queue_pointer, tmp_key);
    }

    for(size_t i = 0; i < LENGTH_QUEUE; i++) {
        std::string tmp_key = randomize->ReturnRandomString();
        AddKey(unactive_queue_pointer, tmp_key);
    }
}

KeyGeneratorClass :: ~KeyGeneratorClass(){
}

std::string KeyGeneratorClass :: ReturnKey(std::queue<std::string> *pointer) {
    std::string tmp_string = pointer->front();
    pointer->pop();
    return tmp_string;
}

void KeyGeneratorClass ::AddKey(std::queue<std::string> *pointer, std::string element) {
    pointer->push(element);
}

std::queue<std::string> *KeyGeneratorClass::ReturnActivePointer() {
    return active_queue_pointer;
}
