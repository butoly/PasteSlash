cmake_minimum_required(VERSION 3.15)
project(url_gen)

set(CMAKE_CXX_STANDARD 14)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.50 REQUIRED COMPONENTS filesystem)

add_subdirectory(google_tests)

add_executable(url_gen main.cpp KeyManager.cpp KeyManager.h KeyGen.cpp KeyGen.h Server.cpp Server.h)
target_link_libraries(url_gen PUBLIC Boost::filesystem)