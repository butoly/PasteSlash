cmake_minimum_required(VERSION 3.14)
project(project C CXX)

set(CMAKE_CXX_STANDARD 17)

install(SCRIPT ${CMAKE_SOURCE_DIR}/cmake/vcpkg.cmake)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

option(BUILD_TESTS "build tests" OFF)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED TRUE)

set(-DCMAKE_TOOLCHAIN_FILE=/vcpkg/packages/grpc_x64-linux/share/gRPC)

find_package(Boost 1.60.0 COMPONENTS system filesystem REQUIRED)
find_package(Protobuf REQUIRED)
find_package(gRPC CONFIG REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

# Генерирует список файлов, соответствуюших выражению *.cpp и помещает его в перменную sources
file(GLOB_RECURSE sources ${PROJECT_SOURCE_DIR}/src/*.cpp)
set(TOOLS-SRC tools/gen/AppLayer.pb.cc tools/gen/AppLayer.grpc.pb.cc)

add_executable(project main.cpp ${sources} ${TOOLS-SRC})

target_link_libraries(project ${Boost_LIBRARIES} gRPC::gpr gRPC::grpc gRPC::grpc++ gRPC::grpc++_alts)

target_include_directories(project PRIVATE inc/)
target_include_directories(project PRIVATE tools/)
