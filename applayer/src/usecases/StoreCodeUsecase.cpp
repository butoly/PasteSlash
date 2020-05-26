#include "usecases/StoreCodeUsecase.h"
#include <unordered_map>

int StoreCodeUsecase::execute() {
    std::string data;
    TCPClient client("127.0.0.1", 5555);

    std::string s = "Sanya, give me hash";

    auto error = client.connect();
    if (error != boost::system::errc::success) {
        return -1;
    }
    std::string receivedData = client.send(s);

    if (receivedData.empty()) {
        return -2;
    }

    code->hash = receivedData;

    dataFormat dc;

    dc.emplace("title" ,code->name);
    dc.emplace("text", code->body);
    dc.emplace("hash", code->hash);

    PasteDBManager::addPaste(dc);

    return 0;
}
