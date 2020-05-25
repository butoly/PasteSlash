#include "usecases/StoreCodeUsecase.h"

int StoreCodeUsecase::execute() {
    std::string data;
    TCPClient client("127.0.0.1", 3000);

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

    //сохранение в бд к нужному user_id

    return 0;
}
