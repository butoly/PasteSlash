#include "grpc_server/ALServer.h"

//
//::grpc::Status ALServer::RegUser(::grpc::ServerContext* context, const ::User* request, ::Token* response) {
//    Models::User* user = converter.UserFromGRPC(request);
//
//    //заглушка для проверки, есть ли такой ник уже в бд
//    bool hasN;
//    if (hasN) {
//
//        return ::grpc::Status(::grpc::ALREADY_EXISTS, "nickname already exists");
//    }
//    //заглушка для проверки, есть ли такой mail уже в бд
//    bool hasE;
//    if (hasE) {
//        return ::grpc::Status(::grpc::ALREADY_EXISTS, "email already exists");
//    }
//
//    //ucase = std::make_unique<RegUserUsecase>(user);
//    //ucase->execute();
//
//    //генерируем access токен
//    std::string token = "token";
//
//    response->set_token(token);
//
//    return ::grpc::Status::OK;
//}
//
//::grpc::Status ALServer::AuthUser(::grpc::ServerContext* context, const ::User* request, ::Token* response) {
//    Models::User* user = converter.UserFromGRPC(request);
//
//    //заглушка для проверки, есть ли такой ник вообще в бд
//    bool hasN;
//    if (!hasN) {
//        return ::grpc::Status(::grpc::NOT_FOUND, "user not found");
//    }
//
////        ucase = std::make_unique<AuthUserUsecase>(user);
////
////        ucase->execute();
//
//    //достаем/генерируем из бд токен
//    std::string token;
//    response->set_token(token);
//
//    return Service::AuthUser(context, request, response);
//}