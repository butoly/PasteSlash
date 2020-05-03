#include "Parser.h"

ReceivedData Parser::parse(std::string& data) {

    bpt::ptree tree;

    std::stringstream str(data);
    bpt::read_json(str, tree);

    recievedData.command = tree.get<std::string>("command");

    BOOST_FOREACH(bpt::ptree::value_type& v, tree.get_child("body")) {
        recievedData.data.insert({v.first, v.second.data()});
    }
    return recievedData;
}

std::string Parser::prepare(std::string& command, std::string& data) {
    std::string responceFile;

    try{
        bpt::ptree tree;

        tree.put("responce.command", command);

        BOOST_FOREACH(responceFile, data){
                        tree.add("responce.modules.module", data);
                    }

        bpt::write_json(responceFile, tree);

    } catch (std::exception const& e) {
        std::cerr << e.what() << std::endl;
    }
    return responceFile;
}