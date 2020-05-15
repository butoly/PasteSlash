#include <thread>
#include <chrono>
#include <mutex>
#include "../inc/KeyGenerator.h"

KeyGeneratorClass :: KeyGeneratorClass() {
    randomize = std::make_shared<RandomizeClass>();
    validator = std::make_shared<KeyValidationClass>();
    active_queue_pointer = std::make_shared<std::queue<std::string>>();
    unactive_queue_pointer = std::make_shared<std::queue<std::string>>();
    generateOfQueues();
    std::thread worker(&KeyGeneratorClass::queueFilling, this);
    worker.detach();
}

void KeyGeneratorClass::startFilling() {
    std::unique_lock<std::mutex> lck(mtx);
    ready = true;
    cv.notify_all(); // notify_one???
}


void KeyGeneratorClass ::queueFilling() {
    std::unique_lock<std::mutex> lck(mtx);
    while (!ready) cv.wait(lck);
    while(unactive_queue_pointer->size() != LENGTH_QUEUE)
        AddKey();
}


KeyGeneratorClass :: ~KeyGeneratorClass(){
}

std::string KeyGeneratorClass :: ReturnKey() {
    std::string tmp_key = active_queue_pointer->front();
    active_queue_pointer->pop();
    if(active_queue_pointer->size() <= MIN_COUNT_ELEMENTS_ARRAY)
    {
        swapQueue();
        startFilling();
    }
    return tmp_key;
}

void KeyGeneratorClass ::swapQueue() {
    std::shared_ptr<std::queue<std::string>> tmp;
    tmp = active_queue_pointer;
    active_queue_pointer = unactive_queue_pointer;
    unactive_queue_pointer = tmp;
}

void KeyGeneratorClass ::AddKey() {
    std::string tmp_key = randomize->ReturnRandomString();
    bool validKey = validator->isValidKey(tmp_key);
    while(!validKey) {
        tmp_key = randomize->ReturnRandomString();
        validKey = validator->isValidKey(tmp_key);
    }
    unactive_queue_pointer->push(tmp_key);
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