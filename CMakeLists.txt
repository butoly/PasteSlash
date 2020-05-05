cmake_minimum_required(VERSION 3.15)
project(url_gen)

set(CMAKE_CXX_STANDARD 14)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.60 REQUIRED COMPONENTS filesystem)
find_package (Threads)

add_subdirectory(tests)

add_executable(url_gen main.cpp src/KeyGenerator.cpp inc/KeyGenerator.h src/Server.cpp inc/Server.h inc/Randomize.h src/Randomize.cpp src/KeyValidation.cpp inc/KeyValidation.h src/DataBaseWorker.cpp inc/DataBaseWorker.h src/Session.cpp inc/Session.h)
target_link_libraries(url_gen PUBLIC Boost::filesystem ${CMAKE_THREAD_LIBS_INIT})