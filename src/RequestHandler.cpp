#include "RequestHandler.h"

void RequestHandler::handle(std::string& data) {
    ReceivedData res;

    res = parser.parse(data);
    std::cout << res.data.at("nickname") << std::endl;

    if (res.command == "register") {
        User user(res.data.at("nickname"), res.data.at("email"), res.data.at("password"));

        ucase = std::make_unique<RegUserUsecase>(user);

        ucase->execute();
    } else if (res.command == "auth") {
        User user(res.data.at("nickname"), res.data.at("password"));

        ucase = std::make_unique<AuthUserUsecase>(user);

        ucase->execute();
    }
}
