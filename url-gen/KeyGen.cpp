#include <queue>
#include "KeyGen.h"

RandomKeyGen::RandomKeyGen(){
    for(int i = 0; i < 1000; i++)
        Queue.push("key");
}

RandomKeyGen::~RandomKeyGen(){

}

std::string RandomKeyGen::getKey()
{
    std::string key = RandomKeyGen::Queue.front();
    pop();

    return key;
}

void RandomKeyGen::pop(){
    Queue.pop();
    Queue.push(generateKey());
}

std::string RandomKeyGen::generateKey(){
    return "OK";
}
