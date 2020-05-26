#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../inc/KeyGenerator.h"

TEST(GeneratorKeyTest,NotEmptyReturnKey) {
    KeyGeneratorClass generator;
    std::string key = generator.ReturnKey();

    ASSERT_NE(key,"");
}