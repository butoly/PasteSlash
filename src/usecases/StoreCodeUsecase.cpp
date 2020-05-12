#include "usecases/StoreCodeUsecase.h"
#include "TCPClient.h"
#include "Parser.h"

void StoreCodeUsecase::execute() {
    std::string data;

    try {
        TCPClient client("127.0.0.1", 3000);

        std::cout << "STORECODEUSECASE";

        std::string s = "{\"command\": \"get hash\"}";

        auto error = client.connect();
        if (error != boost::system::errc::success) {
            return;
        }

        auto receivedData = client.send(s);

        Parser p;
        std::string hash = p.parseHash(receivedData);

        code.hash = hash;

        //сохранение в бд

    } catch(std::exception& e) {

    }
}