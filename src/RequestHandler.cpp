#include "RequestHandler.h"

void RequestHandler::handle(std::string& data, std::string& response) {
    Models::ReceivedData res;

    res = parser.parse(data);

    if (res.command == "register") {

        std::string nickname = res.data.at("nickname");
        std::string email = res.data.at("email");
        std::string password = res.data.at("password");

        //заглушка для проверки, есть ли такой ник уже в бд
        bool hasN;
        if (hasN) {
            response = "NICKNAME ALREADY EXIST";
            return;
        }
        //заглушка для проверки, есть ли такой mail уже в бд
        bool hasE;
        if (hasE) {
            response = "EMAIL ALREADY EXIST";
            return;
        }

        Models::User user(nickname, email, password);

        ucase = std::make_unique<RegUserUsecase>(user);

        ucase->execute();

    } else if (res.command == "auth") {
        std::string nickname = res.data.at("nickname");

        //заглушка для проверки, есть ли такой ник вообще в бд
        bool hasN;
        if (!hasN) {
            response = "NICKNAME NOT FOUND";
            return;
        }

        Models::User user(nickname, res.data.at("password"));

        ucase = std::make_unique<AuthUserUsecase>(user);

        ucase->execute();

    } else if (res.command == "store") {

        std::string defaultHash = "0";

        Models::Code code(defaultHash, res.data.at("name"), res.data.at("body"));

        ucase = std::make_unique<StoreCodeUsecase>(code);

        ucase->execute();

    } else if (res.command == "get code") {


    } else if (res.command == "get hash") {

        std::cout << res.command << std::endl;

    } else {std::cout << "ok" << std::endl;}
}
