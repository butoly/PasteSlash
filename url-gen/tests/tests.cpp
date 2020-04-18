#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../inc/KeyManager.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::std::string;

class MockKeyManager : public KeyManager {
public:
    MOCK_METHOD0(CheckValidationKey, std::string());
};

TEST(KeyManager, ReturnTest) {
    MockKeyManager keyManager;
    EXPECT_CALL(keyManager, CheckValidationKey()).Times(1).WillOnce(Return(true));
    EXPECT_CALL(keyManager, CheckValidationKey()).Times(1).WillOnce(Return(false));
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
