#ifndef URL_GEN_KEYGENERATOR_H
#define URL_GEN_KEYGENERATOR_H

#include <string>
#include <queue>
#include <memory>

#include "Randomize.h"
#include "KeyValidation.h"

#define LENGTH_QUEUE 10 //Количество элементов в очередях
#define MIN_COUNT_ELEMENTS_ARRAY 4// Порог при котором необходимо поменять очереди и начать заполнять опустевшую

class KeyGeneratorClass {
public:
    KeyGeneratorClass();
    ~KeyGeneratorClass();

    void AddKey(); // Добавления ключа в очередь
    std::string ReturnKey(); // Возвращение ключа из активной очередь

private:
    std::shared_ptr<std::queue<std::string>> active_queue_pointer; // Очередь из которой будут выдаваться ключи.
    std::shared_ptr<std::queue<std::string>> unactive_queue_pointer; // Очередь которая будет заполняться асинхронно

    std::shared_ptr<RandomizeClass> randomize; // Класс для генерации строк
    std::shared_ptr<KeyValidationClass> validator; // Класс для проверки ключей

    void swapQueue(); // Смена указателей на очереди
    void generateOfQueues(); // Заполнение очередей при вызове конструктора класса
    void queueFilling(); // Функция заполняющая неактивную очередь в второстепенном потоке
};

#endif //URL_GEN_KEYGENERATOR_H
