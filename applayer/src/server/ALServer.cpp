#include "server/ALServer.h"

ALServer::ALServer(const std::string& ip, const std::string& port) {
    std::string address = ip + ":" + port;
    builder.AddListeningPort(address, ::grpc::InsecureServerCredentials());
}
ALServer::~ALServer() {
    server->Shutdown();
    cq->Shutdown();
}

void ALServer::run() {
    builder.RegisterService(&service);
    cq = builder.AddCompletionQueue();
    server = builder.BuildAndStart();

    void* tag;
    bool ok;

    new RegUserCD(&service, cq.get());
    new AuthUserCD(&service, cq.get());
    new CheckTokenCD(&service, cq.get());
    new StoreCodeCD(&service, cq.get());
    new GetCodeCD(&service, cq.get());
    new DeleteCodeCD(&service, cq.get());
    new GetAllHashesCD(&service, cq.get());
    //остльные
    while (true) {
        GPR_ASSERT(cq->Next(&tag, &ok));
        BaseCallData* callData = static_cast<BaseCallData*>(tag);
        callData->proceed(ok);
    }
}
