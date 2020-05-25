#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "inc/StoreCodeHandler.h"
#include "inc/GetCodeHandler.h"


class StoreCodeHandlerTest : public ::testing::Test {
public:
    explicit StoreCodeHandlerTest() : request(), response(nullptr) {}
protected:
    void SetUp() override {
        request.push_back(1);
        response = nullptr;
        handler = new StoreCodeHandler(request, response);
    }

    void TearDown() final {
        delete handler;
    }
    std::vector<int> request;
    int* response;
    StoreCodeHandler* handler = nullptr;
};

TEST_F(StoreCodeHandlerTest, SuccessTest) {

    EXPECT_NO_THROW(handler->execute());
}

class GetCodeHandlerTest : public ::testing::Test {
public:
    explicit GetCodeHandlerTest() : request(), response(nullptr) {}
protected:
    void SetUp() override {
        request.push_back(1);
        response = nullptr;
        handler = new GetCodeHandler(request, response);
    }

    void TearDown() final {
        delete handler;
    }
    std::vector<int> request;
    int* response;
    GetCodeHandlerTest* handler = nullptr;
};

TEST_F(GetCodeHandlerTest, SuccessTest) {

    EXPECT_NO_THROW(handler->execute());
}