#include "inc/Randomize.h"
#include "inc/KeyGenerator.h"

//std::queue<std::string> db;

int main() {

    KeyGeneratorClass *key_generator = new KeyGeneratorClass();

    for (int i = 0; i < 15; i++) {
        std::cout << key_generator->ReturnKey() << std::endl;
    }

    return 0;
}