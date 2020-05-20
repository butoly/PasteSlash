#include "Parser.h"

ReceivedData Parser::parse(std::string& data) {

    bpt::ptree tree;

    std::stringstream str(data);
    bpt::read_json(str, tree);

    receivedData.command = tree.get<std::string>("command");

    std::cout << receivedData.command << std::endl;

    BOOST_FOREACH(bpt::ptree::value_type& v, tree.get_child("body")) {
                    receivedData.data.insert({v.first, v.second.data()});
    }
    return receivedData;
}

std::string Parser::parseHash(std::string& data) {
    bpt::ptree tree;

    std::stringstream str(data);
    bpt::read_json(str, tree);

    return tree.get<std::string>("hash");
}

std::string Parser::prepare(std::string& command, std::string& data) {
    std::string responceFile;

    try{
        bpt::ptree tree;

        tree.put("command", command);

        BOOST_FOREACH(responceFile, data){
                        tree.add("", data);
                    }

        bpt::write_json(responceFile, tree);

    } catch (std::exception const& e) {
        std::cerr << e.what() << std::endl;
    }
    return responceFile;
}