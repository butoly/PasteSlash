cmake_minimum_required(VERSION 3.15)
project(url_gen)

set(CMAKE_CXX_STANDARD 14)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.50 REQUIRED COMPONENTS filesystem)

add_subdirectory(tests)

add_executable(url_gen main.cpp src/KeyManager.cpp inc/KeyManager.h src/KeyGenerator.cpp inc/KeyGenerator.h src/Server.cpp inc/Server.h inc/Randomize.h src/Randomize.cpp)
target_link_libraries(url_gen PUBLIC Boost::filesystem)