#ifndef URL_GEN_KEYGENERATOR_H
#define URL_GEN_KEYGENERATOR_H

#include <string>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "Randomize.h"
#include "KeyValidation.h"

#define LENGTH_QUEUE 3 //Количество элементов в очередях
#define MIN_COUNT_ELEMENTS_ARRAY 2// Порог при котором необходимо поменять очереди и начать заполнять опустевшую

class KeyGeneratorClass {
public:
    KeyGeneratorClass();
    ~KeyGeneratorClass();

    std::string ReturnKey(); // Возвращение ключа из активной очередь

private:
    std::shared_ptr<std::queue<std::string>> active_queue_pointer; // Очередь из которой будут выдаваться ключи.
    std::shared_ptr<std::queue<std::string>> unactive_queue_pointer; // Очередь которая будет заполняться асинхронно

    RandomizeClass& randomizer = RandomizeClass::getInstance(); // Класс для генерации строк синглтон
   // KeyValidationClass& validator = KeyValidationClass::getInstance(); // Класс проверки валидности ключа синглтон

    void swapQueue(); // Смена указателей на очереди
    void generateOfQueues(); // Заполнение очередей при вызове конструктора класса
    void queueFilling(); // Функция заполняющая неактивную очередь в второстепенном потоке
    void startFilling();
    void AddKey(); // Добавления ключа в очередь

    std::mutex mtx;
    std::condition_variable cv;
    bool ready = false;
    std::thread worker;
};

#endif //URL_GEN_KEYGENERATOR_H
