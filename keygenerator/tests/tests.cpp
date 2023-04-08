#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../inc/KeyGenerator.h"

TEST(GeneratorKeyTest,NotEmptyReturnKey) {
    KeyGeneratorClass generator;
    std::string key = generator.ReturnKey();
    ASSERT_NE(key, "");
}

TEST(ValidatorKeyTest,ValidKey) {
    std::string key = "H4Y83H3";
    KeyValidationClass& validator = KeyValidationClass::getInstance();
    ASSERT_EQ(true, validator.isValidKey(key));
}

TEST(ValidatorKeyTest, CheckNonNullSingleton) {
    KeyValidationClass& validator = KeyValidationClass::getInstance();
    EXPECT_NE(&validator, nullptr);
}

TEST(ValidatorKeyTest,CheckSingleton) {
    KeyValidationClass& validator1 = KeyValidationClass::getInstance();
    KeyValidationClass& validator2 = KeyValidationClass::getInstance();
    ASSERT_EQ(&validator1, &validator2);
}

TEST(RandomizerTests,CheckSingleton) {
    RandomizeClass& randomizer = RandomizeClass::getInstance();
    EXPECT_NE(&randomizer, nullptr);
}

TEST(RandomizerTests,CheckGetRandomString) {
    RandomizeClass& randomizer = RandomizeClass::getInstance();
    std::string data = randomizer.ReturnRandomString();
    EXPECT_NE(data, "");
}