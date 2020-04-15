cmake_minimum_required(VERSION 3.10.2)

project(Google_tests)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(tests_run tests.cpp ../KeyManager.cpp ../KeyManager.h ../KeyGen.cpp ../KeyGen.h ../Server.cpp ../Server.h)

target_link_libraries(tests_run ${GTEST_LIBRARIES} pthread)
