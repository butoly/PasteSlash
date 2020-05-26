#ifndef WEBSERVER_ALCLIENT_HPP
#define WEBSERVER_ALCLIENT_HPP

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <grpcpp/grpcpp.h>
#include <grpc/support/log.h>

#include "AppLayer.grpc.pb.h"

using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;
using std::string;
using std::vector;

User MakeUser(const string& nickname, const string& email,
    const string& password);

Error MakeError(const string& message);

AccessToken MakeAccessToken(const string& token, long user_id);

Token MakeToken(const string& token);

Hash MakeHash(const string& value);

Hashes MakeHashes(Hash hashes);

Code MakeCode(const string& name, const string& text, long user_id);

class AppLayerClient {
public:
explicit AppLayerClient(std::shared_ptr<Channel> channel) :
    stub_(AppLayer::NewStub(channel)) {}

    string AuthUser(const string& nickname, const string& email,
        const string& password, string& token);

    string RegUser(const string& nickname, const string& email,
        const string& password, string& token);

    string StoreCode(const string& name, const string& text,
        string& token, string& hash);

    string GetCode(const string& hash, string& name, string& text);

    string DeleteCode(const string& hash, string& error);

    string GetAllHashes(string nickname, string email, string password,
        vector<string>& hashes);

    const string positive_reply = "OK";

private:
    std::unique_ptr<AppLayer::Stub> stub_;
};

#endif // WEBSERVER_ALCLIENT_HPP
