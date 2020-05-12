#include <queue>
#include <thread>
#include <chrono>
#include "../inc/KeyGenerator.h"

KeyGeneratorClass :: KeyGeneratorClass() {
    randomize = new RandomizeClass();
    active_queue_pointer = &queue1;
    unactive_queue_pointer = &queue2;
    generateOfQueues();
}

KeyGeneratorClass :: ~KeyGeneratorClass(){
}

std::string KeyGeneratorClass :: ReturnKey() {
    std::string tmp_string = active_queue_pointer->front();
    active_queue_pointer->pop();
    if(active_queue_pointer->size() <= MIN_COUNT_ELEMENTS_ARRAY)
    {
        swapQueue();
        std::thread t(&KeyGeneratorClass::QueueFilling, this);
        t.detach();
    }
    return tmp_string;
}

void KeyGeneratorClass ::swapQueue() {
    std::queue<std::string> *tmp;
    tmp = active_queue_pointer;
    active_queue_pointer = unactive_queue_pointer;
    unactive_queue_pointer = tmp;
}

void KeyGeneratorClass ::AddKey() {
    std::string element = randomize->ReturnRandomString();
    unactive_queue_pointer->push(element);
}

void KeyGeneratorClass ::QueueFilling() {
    std::this_thread::sleep_for(std::chrono::seconds(5));
    while(unactive_queue_pointer->size() != LENGTH_QUEUE)
        AddKey();
}

void KeyGeneratorClass::generateOfQueues() {
    for(size_t i = 0; i < LENGTH_QUEUE; i++) {
        std::string tmp_key = randomize->ReturnRandomString();
        active_queue_pointer->push(tmp_key);
    }

    for(size_t i = 0; i < LENGTH_QUEUE; i++) {
        std::string tmp_key = randomize->ReturnRandomString();
        unactive_queue_pointer->push(tmp_key);
    }

    //TODO запись на постоянную память
}
