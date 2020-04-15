#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "inc/Parser.h"
#include "inc/Application.h"
#include "inc/Socket.h"

TEST(TestingParser, Parse) {

    auto expected_result = 0;
    std::string str = "{\"data\": \"value\", \"data2\": \"value2\"}";
    Parser p;
    auto result = p.parse(str);

    ASSERT_EQ(result, expected_result);
}

TEST(TestingSocket, ResultRecv) {
    auto expected_result = 0;
    Socket s;

    ASSERT_EQ(s.recv(), expected_result);
}

TEST(TestingSocket, ExeptionRecv) {

    EXPECT_NO_THROW(s.recv());
}

TEST(TestingSocket, ExeptionSend) {

    EXPECT_NO_THROW(s.send());
}
