cmake_minimum_required(VERSION 3.10.2)

project(Google_tests)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(tests_run tests.cpp ../src/KeyGenerator.cpp ../inc/KeyGenerator.h ../src/Server.cpp ../inc/Server.h ../inc/Randomize.h ../src/Randomize.cpp ../src/KeyValidation.cpp ../inc/KeyValidation.h ../src/Session.cpp ../inc/Session.h ../src/Parser.cpp ../inc/Parser.h)

target_link_libraries(tests_run ${GTEST_LIBRARIES} pthread)
