#ifndef URL_GEN_DATABASEWORKER_H
#define URL_GEN_DATABASEWORKER_H

class DataBaseWorkerClass {
public:
    DataBaseWorkerClass();
    ~DataBaseWorkerClass();
    void AddPaste(std::string paste, std::string key);
    bool CheckKey(std::string key);
};

#endif //URL_GEN_DATABASEWORKER_H
