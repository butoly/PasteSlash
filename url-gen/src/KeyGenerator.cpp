#include <queue>
#include "../inc/KeyGenerator.h"

KeyGeneratorClass :: KeyGeneratorClass() {

    RandomizeClass *randomize = new RandomizeClass();

    for (int i = 0; i < 100; i++) {
        queue1.push(randomize->ReturnRandomString());
        queue2.push(randomize->ReturnRandomString());
    }

    active_queue_pointer = &queue1;
}

KeyGeneratorClass :: ~KeyGeneratorClass(){
}

std::string KeyGeneratorClass ::ReturnKey() {
    std::string tmp_string = queue1.front();
    queue1.pop();
    return tmp_string;
}

void KeyGeneratorClass ::AddKey() {

}
