cmake_minimum_required(VERSION 3.14)
project(project C CXX)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

option(BUILD_TESTS "build tests" OFF)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED TRUE)

find_package(Boost 1.68.0 COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# Генерирует список файлов, соответствуюших выражению *.cpp и помещает его в перменную sources
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(project main.cpp ${sources})
target_link_libraries(project ${Boost_LIBRARIES})

target_include_directories(project PRIVATE inc/)

if (BUILD_TESTS)
    # gtest settings

    # Конфигурирует CMakeLists.txt для тестов
    # Фактически копирует содержимое .in в указанный файл
    configure_file(CMakeLists.txt.in gtest/googletest-download/CMakeLists.txt)

    # Выполнить команду cmake с указанным генератором Makefile (ключ -G) в указанной WORKING_DIRECTORY
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/gtest/googletest-download)

    # Выполнить команду cmake c ключом --build
    execute_process(COMMAND ${CMAKE_COMMAND} --build .
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/gtest/googletest-download)

    # Добавить поддиректории к текущему проекту
    add_subdirectory(${CMAKE_BINARY_DIR}/gtest/googletest-src ${CMAKE_BINARY_DIR}/gtest/googletest-build)

    # test_sources со всеми cpp файлами из tests
    file(GLOB tests_sources ${PROJECT_SOURCE_DIR}/tests/*.cpp)

    # Бинарник test, собранный на основе файлов тестов и файлов исходников, которые мы тестируем
    add_executable(test ${tests_sources} ${sources} tests/handlersTests.cpp)

    target_link_libraries(test gtest_main gmock_main)

    target_include_directories(test PRIVATE .)
endif()
