#include "../include/Connection.h"
#include <fstream>
#define DEBUG 1

std::string readFileInString(const std::string& fileName) {
    std::ifstream ifs(fileName);
    std::string content( (std::istreambuf_iterator<char>(ifs)),
                         (std::istreambuf_iterator<char>()));
    return content;
}

Connection::Connection() :
    connection(readFileInString("pgConfig.txt")) {}

Connection::Connection(const std::string& configFileName):
    connection(readFileInString(configFileName)) {}

bool Connection::isActive() {
    return connection.is_open();
}

#ifdef DEBUG
void printParsedResult(const queryResultFormat& parsedResult){
    std::cout << "\nMap:" << std::endl;
    for (auto& i : parsedResult) {
        for (auto& j : i) {
            std::cout << j.first << " = " << j.second << std::endl;
        }
        std::cout << std::endl;
    }
}
#endif

queryResultFormat parsePGResult(const pqxx::result& result) {
    queryResultFormat parsedResult;

    for (pqxx::result::const_iterator row = result.begin(); row != result.end();
         row++) {
         dataFormat map;

        for (auto&& field : row)
            map[field.name()] = field.c_str();

        parsedResult.push_back(map);
    }

#ifdef DEBUG
    printParsedResult(parsedResult);
#endif

    return parsedResult;
}

void Connection::execPostQuery(const std::string& sqlQuery) {
    try {
        pqxx::work worker{connection};
        worker.exec0(sqlQuery);
        worker.commit();
    }
    catch (const std::exception& exception) {
        std::cout << exception.what() << std::endl;
    }
}

queryResultFormat Connection::execGetQuery(const std::string& sqlQuery) {
    pqxx::result result;
    try {
        pqxx::work worker{connection};
        result = worker.exec(sqlQuery);
    }
    catch (const std::exception& exception) {
        std::cout << exception.what() << std::endl;
    }

    return parsePGResult(result);
}

void Connection::execPostQueryFromFile(const std::string& fileName) {
    std::string sqlQuery = readFileInString(fileName);
    execPostQuery(sqlQuery);
}

queryResultFormat Connection::execGetQueryFromFile(const std::string& fileName) {
    std::string sqlQuery = readFileInString(fileName);
    return execGetQuery(sqlQuery);
}
