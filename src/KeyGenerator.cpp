#include <queue>
#include "../inc/KeyGenerator.h"

KeyGeneratorClass :: KeyGeneratorClass() {

    RandomizeClass *randomize = new RandomizeClass();

    active_queue_pointer = &queue1;

    for (size_t i = 0; i < LENGTH_QUEUE; i++) {
        std::string tmp_key = randomize->ReturnRandomString();
        if(tmp_key == queue1.front())
            tmp_key = randomize->ReturnRandomString();
        queue1.push(tmp_key);
    }

}

KeyGeneratorClass :: ~KeyGeneratorClass(){
}

std::string KeyGeneratorClass :: ReturnKey() {
    std::string tmp_string = queue1.front();
    queue1.pop();
    return tmp_string;
}

void KeyGeneratorClass ::AddKey() {

}
