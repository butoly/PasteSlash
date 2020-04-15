#ifndef URL_GEN_KEYGEN_H
#define URL_GEN_KEYGEN_H

#include <string>
#include <queue>

class IKeyGen {
private:
    virtual std::string generateKey() = 0;
    virtual void pop() = 0;
};

class RandomKeyGen : IKeyGen {
public:
    explicit RandomKeyGen();
    virtual ~RandomKeyGen();
    std::string getKey();

private:
    void pop() override;
    std::string generateKey() override;
    std::queue<std::string> Queue;
};


#endif //URL_GEN_KEYGEN_H
