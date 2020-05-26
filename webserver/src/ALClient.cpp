#include "ALClient.h"

User MakeUser(const string& nickname, const string& email,
    const string& password) {
    User u;
    u.set_nickname(nickname);
    u.set_email(email);
    u.set_password(password);
    return u;
}

Error MakeError(const string& message) {
    Error er;
    er.set_message(message);
    return er;
}

AccessToken MakeAccessToken(const string& token, long user_id) {
    AccessToken at;
    at.set_token(token);
    at.set_user_id(user_id);
    return at;
}

Token MakeToken(const string& token) {
    Token t;
    t.set_token(token);
    return t;
}

Hash MakeHash(const string& value) {
    Hash h;
    h.set_value(value);
    return h;
}

Hashes MakeHashes(Hash hashes) {
    Hashes h;
    return h;
}

Code MakeCode(const string& name, const string& text, long user_id) {
    Code c;
    c.set_name(name);
    c.set_text(text);
    c.set_user_id(user_id);
    return c;
}

string AppLayerClient::AuthUser(const string& nickname, const string& email,
    const string& password, string& token) {
    User user = MakeUser(nickname, email, password);
    Token tk;

    ClientContext context;
    CompletionQueue cq;
    Status status;

    std::unique_ptr<ClientAsyncResponseReader<Token>> rpc(
        stub_->PrepareAsyncAuthUser(&context, user, &cq));
    rpc->StartCall();
    
    rpc->Finish(&tk, &status, (void*)1);
    void* got_tag;
    bool ok = false;

    GPR_ASSERT(cq.Next(&got_tag, &ok));
    GPR_ASSERT(got_tag == (void*)1);
    GPR_ASSERT(ok);

    token = tk.token();
    if (status.ok()) {
        return positive_reply;
    } else {
        return "RPC failed";
    }
}

string AppLayerClient::RegUser(const string& nickname, const string& email,
    const string& password, string& token) {
    User user = MakeUser(nickname, email, password);
    Token tk;

    ClientContext context;
    CompletionQueue cq;
    Status status;

    std::unique_ptr<ClientAsyncResponseReader<Token>> rpc(
        stub_->PrepareAsyncRegUser(&context, user, &cq));
    rpc->StartCall();
    
    rpc->Finish(&tk, &status, (void*)1);
    void* got_tag;
    bool ok = false;

    GPR_ASSERT(cq.Next(&got_tag, &ok));
    GPR_ASSERT(got_tag == (void*)1);
    GPR_ASSERT(ok);

    token = tk.token();
    if (status.ok()) {
        return positive_reply;
    } else {
        return "RPC failed";
    }
}

Status AppLayerClient::CheckToken(string& token, long& user_id, string& error) {
    Token tk = MakeToken(token);
    AccessToken acs_token;

    ClientContext context;
    CompletionQueue cq;
    Status status;

    std::unique_ptr<ClientAsyncResponseReader<AccessToken>> rpc_add(
        stub_->PrepareAsyncCheckToken(&context, tk, &cq));
    rpc_add->StartCall();
    
    rpc_add->Finish(&acs_token, &status, (void*)1);
    void* got_tag_add;
    bool ok_add = false;

    GPR_ASSERT(cq.Next(&got_tag_add, &ok_add));
    GPR_ASSERT(got_tag_add == (void*)1);
    GPR_ASSERT(ok_add);

    token = acs_token.token();
    user_id = acs_token.user_id();
    error = acs_token.error().message();
    return status;
}

string AppLayerClient::StoreCode(const string& name, const string& text,
    string& token, string& hash) {
    long user_id;
    string error;
    Status st = CheckToken(token, user_id, error);
    if (!st.ok()) {
        return error;
    }

    Code code = MakeCode(name, text, user_id);
    Hash hs;

    ClientContext context;
    CompletionQueue cq;
    Status status;

    std::unique_ptr<ClientAsyncResponseReader<Hash>> rpc(
        stub_->PrepareAsyncStoreCode(&context, code, &cq));
    rpc->StartCall();
    
    rpc->Finish(&hs, &status, (void*)1);
    void* got_tag;
    bool ok = false;

    GPR_ASSERT(cq.Next(&got_tag, &ok));
    GPR_ASSERT(got_tag == (void*)1);
    GPR_ASSERT(ok);

    hash = hs.value();
    if (status.ok()) {
        return positive_reply;
    } else {
        return "RPC failed";
    }
}

string AppLayerClient::GetCode(const string& hash, string& name, string& text) {
    Hash hs = MakeHash(hash);
    Code code;

    ClientContext context;
    CompletionQueue cq;
    Status status;

    std::unique_ptr<ClientAsyncResponseReader<Code>> rpc(
        stub_->PrepareAsyncGetCode(&context, hs, &cq));
    rpc->StartCall();
    
    rpc->Finish(&code, &status, (void*)1);
    void* got_tag;
    bool ok = false;

    GPR_ASSERT(cq.Next(&got_tag, &ok));
    GPR_ASSERT(got_tag == (void*)1);
    GPR_ASSERT(ok);

    name = code.name();
    text = code.text();
    if (status.ok()) {
        return positive_reply;
    } else {
        return "RPC failed";
    }
}

string AppLayerClient::DeleteCode(const string& hash, string& token, string& error) {
    long user_id;
    Status st = CheckToken(token, user_id, error);
    if (!st.ok()) {
        return error;
    }

    Hash hs = MakeHash(hash);
    Error err;

    ClientContext context;
    CompletionQueue cq;
    Status status;

    std::unique_ptr<ClientAsyncResponseReader<Error>> rpc(
        stub_->PrepareAsyncDeleteCode(&context, hs, &cq));
    rpc->StartCall();
    
    rpc->Finish(&err, &status, (void*)1);
    void* got_tag;
    bool ok = false;

    GPR_ASSERT(cq.Next(&got_tag, &ok));
    GPR_ASSERT(got_tag == (void*)1);
    GPR_ASSERT(ok);

    error = err.message();
    if (status.ok()) {
        return positive_reply;
    } else {
        return "RPC failed";
    }
}

string AppLayerClient::GetAllHashes(const string& nickname,
    string& token, vector<string>& hashes) {
    long user_id;
    string error;
    Status st = CheckToken(token, user_id, error);
    if (!st.ok()) {
        return error;
    }

    string email = "";
    string password = "";
    User user = MakeUser(nickname, email, password);
    Hashes hs;

    ClientContext context;
    CompletionQueue cq;
    Status status;

    std::unique_ptr<ClientAsyncResponseReader<Hashes>> rpc(
        stub_->PrepareAsyncGetAllHashes(&context, user, &cq));
    rpc->StartCall();
    
    rpc->Finish(&hs, &status, (void*)1);
    void* got_tag;
    bool ok = false;

    GPR_ASSERT(cq.Next(&got_tag, &ok));
    GPR_ASSERT(got_tag == (void*)1);
    GPR_ASSERT(ok);
    
    for (auto hash = hs.hashes().begin(); hash != hs.hashes().end(); ++hash) {
        hashes.push_back(hash->value());
    }
    if (status.ok()) {
        return positive_reply;
    } else {
        return "RPC failed";
    }
}
