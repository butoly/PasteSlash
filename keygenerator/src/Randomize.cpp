#include "../inc/Randomize.h"

RandomizeClass :: RandomizeClass() {
    InitGenerator(generator);
}

std::string RandomizeClass :: ReturnRandomString() {

    std::string random_string;
    for (int i = 0; i < current_length; i++)
        random_string += pool[RandomInt(generator, 0, 61)];

    return random_string;
}

void RandomizeClass::InitGenerator(RandomizeClass::PRNG &generator) {
    std::random_device device;
    generator.engine.seed(device());
}

unsigned RandomizeClass::RandomInt(RandomizeClass::PRNG &generator, unsigned min_value, unsigned max_value) {
    // Создаём распределение
    std::uniform_int_distribution<unsigned> distribution(min_value, max_value);
    // Вычисляем псевдослучайное число и вызывем распределение как функцию,
    // передав генератор произвольных целых чисел как аргумент.
    return distribution(generator.engine);
}

RandomizeClass &RandomizeClass::getInstance() {
    static RandomizeClass randomizer;
    return randomizer;
}