#ifndef PROJECT_GETALLHASHESUSECASE_H
#define PROJECT_GETALLHASHESUSECASE_H

#include <iostream>
#include "Models.h"
#include "AbstractUsecase.h"
#include "gen/AppLayer.grpc.pb.h"
#include <grpcpp/grpcpp.h>

class GetAllHashesUsecase : public AbstractUsecase {
private:
    Models::User user;
    std::vector<std::string>* hashes;

public:
    GetAllHashesUsecase(Models::User& u, std::vector<std::string>* h) : user(u), hashes(h) {};
    ~GetAllHashesUsecase() = default;

    int execute() override;
};


#endif //PROJECT_GETALLHASHESUSECASE_H
