#include "RequestHandler.h"

void RequestHandler::handle(std::string& data) {
    ReceivedData res;

    res = parser.parse(data);

    if (res.command == "register") {
        User user(res.data.at("nickname"), res.data.at("email"), res.data.at("password"));

        ucase = std::make_unique<RegUserUsecase>(user);

        ucase->execute();
    } else if (res.command == "auth") {
        User user(res.data.at("nickname"), res.data.at("password"));

        ucase = std::make_unique<AuthUserUsecase>(user);

        ucase->execute();

    } else if (res.command == "store") {
        std::string defaultHash = "0";

        Code code(defaultHash, res.data.at("name"), res.data.at("body"));

        ucase = std::make_unique<StoreCodeUsecase>(code);

        ucase->execute();

    } else if (res.command == "get hash") {

        std::cout << res.command << std::endl;

    } else {std::cout << "ok" << std::endl;}
}
