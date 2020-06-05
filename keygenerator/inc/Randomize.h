#ifndef URL_GEN_RANDOMIZE_H
#define URL_GEN_RANDOMIZE_H

#include <string>
#include <iostream>
#include <ctime>
#include <random>
#include <cassert>
#include <exception>

#define STRING_LENGTH 8

class RandomizeClass {
public:
    std::string ReturnRandomString();
    static RandomizeClass& getInstance();
private:
    RandomizeClass();
    ~RandomizeClass() = default;

    RandomizeClass(RandomizeClass const&) = delete;
    RandomizeClass& operator= (RandomizeClass const&) = delete;

    const char pool[62] = {'a','b','C','d','e','f','g','h','i','j','k','l','m','n','o','p','q',
                     'r','s','t','u','v','w','x','y','z',
                     'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q',
                     'R','S','T','U','V','W','X','Y','Z',
                     '1','2','3','4','5','6','7','8','9','0'};

    int current_length = STRING_LENGTH;

    //Вихрь Мерсенна
    struct PRNG
    {
        std::mt19937 engine;
    };

    PRNG generator;
    static void InitGenerator(PRNG& generator);
    static unsigned RandomInt(PRNG& generator, unsigned min_value, unsigned max_value);
};

#endif //URL_GEN_RANDOMIZE_H
