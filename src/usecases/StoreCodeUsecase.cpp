#include "usecases/StoreCodeUsecase.h"
#include "TCPClient.h"
#include "Parser.h"

void StoreCodeUsecase::execute() {
    std::string data;

    try {
        TCPClient client;

        std::cout << "STORECODEUSECASE";

        std::string s = "{\"command\": \"get hash\"}";

        std::string receivedData = client.run("127.0.0.1", 3000, s);

        Parser p;
        std::string hash = p.parseHash(receivedData);

        code.hash = hash;

    } catch(std::exception& e) {

    }
}