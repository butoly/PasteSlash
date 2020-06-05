#include <thread>
#include <chrono>
#include <mutex>
#include "../inc/KeyGenerator.h"

KeyGeneratorClass :: KeyGeneratorClass() {
    active_queue_pointer = std::make_shared<std::queue<std::string>>();
    unactive_queue_pointer = std::make_shared<std::queue<std::string>>();
    generateOfQueues();
    worker = new std::thread(&KeyGeneratorClass::queueFilling, this);
}

void KeyGeneratorClass::startFilling() {
    ready = true;
    cv.notify_one();
}

void KeyGeneratorClass::queueFilling() {
    std::unique_lock<std::mutex> lck(mtx);
    while (!ready) {
        cv.wait(lck);
        while (unactive_queue_pointer->size() < LENGTH_QUEUE)
            AddKey();
        ready = false;
    };
}

KeyGeneratorClass :: ~KeyGeneratorClass(){
    worker->join();
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
    std::string tmp_key = randomizer.ReturnRandomString();
    bool validKey = validator.isValidKey(tmp_key);
    while(!validKey) {
        tmp_key = randomizer.ReturnRandomString();
        validKey = validator.isValidKey(tmp_key);
    }
    unactive_queue_pointer->push(tmp_key);
}

void KeyGeneratorClass::generateOfQueues() {
    for(size_t i = 0; i < LENGTH_QUEUE; i++) {
        std::string tmp_key = randomizer.ReturnRandomString();
        active_queue_pointer->push(tmp_key);
    }

    for(size_t i = 0; i < LENGTH_QUEUE; i++) {
        std::string tmp_key = randomizer.ReturnRandomString();
        unactive_queue_pointer->push(tmp_key);
    }
}