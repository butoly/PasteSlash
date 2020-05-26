#include "usecases/StoreCodeUsecase.h"
#include <unordered_map>

int StoreCodeUsecase::execute() {
    std::string data;
    TCPClient client("127.0.0.1", 3002);

    std::string s = "helloSanya";

    auto error = client.connect();
    if (error != boost::system::errc::success) {
        return -1;
    }
    std::string receivedData = client.send(s);

    if (receivedData.empty()) {
        return -2;
    }

    code->hash = receivedData;

    bool isSuccess = PasteDBManager::addPaste(code->body, code->hash, "yletamitlu", code->name);

    if (!isSuccess) {
        return -2;
    }

    return 0;
}
