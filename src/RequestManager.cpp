#include "../inc/RequestManager.h"

void handle(std::string data) {
    parser.parse(data);

    // response, request fields
    handler = new StoreCodeHandler();
    handler->execute();

    sender.send(); // send response
}