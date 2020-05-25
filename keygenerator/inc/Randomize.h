#ifndef URL_GEN_RANDOMIZE_H
#define URL_GEN_RANDOMIZE_H

#include <string>
#include <iostream>
#include <ctime>
#include <random>
#include <cassert>
#include <exception>

class RandomizeClass {
public:
    RandomizeClass();
    ~RandomizeClass();

    std::string ReturnRandomString();
private:
    const char pool[62] = {'a','b','C','d','e','f','g','h','i','j','k','l','m','n','o','p','q',
                     'r','s','t','u','v','w','x','y','z',
                     'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q',
                     'R','S','T','U','V','W','X','Y','Z',
                     '1','2','3','4','5','6','7','8','9','0'};

    int current_length = 8;

    //Вихрь Мерсенна
    struct PRNG
    {
        std::mt19937 engine;
    };

    PRNG generator;
    void InitGenerator(PRNG& generator);
    unsigned RandomInt(PRNG& generator, unsigned min_value, unsigned max_value);
};

#endif //URL_GEN_RANDOMIZE_H
