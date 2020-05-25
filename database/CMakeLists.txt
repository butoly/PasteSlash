cmake_minimum_required(VERSION 3.12)
project(dbAPI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpqxx -lpq")

set(PQXX /usr/local/include/pqxx)
set(SOURCE_FILES src/Connection.cpp src/Database.cpp src/SqlGenerator.cpp
        src/DatabaseObject.cpp src/PasteDBManager.cpp
        src/UserDBManager.cpp)

find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)

#add_executable(test test/test.cpp include/*.h src/*.cpp)
#add_executable(test cleaner.cpp ${SOURCE_FILES})

#add_executable(cleaner cleaner.cpp ${SOURCE_FILES})
#add_executable(test_con main.cpp ${SOURCE_FILES})
add_library(dbAPI STATIC ${SOURCE_FILES})
#TARGET_LINK_LIBRARIES(test_con  ${PQXX_LIB} ${PQ_LIB})
#TARGET_LINK_LIBRARIES(cleaner ${PQXX_LIB} ${PQ_LIB})

TARGET_LINK_LIBRARIES(dbAPI ${PQXX_LIB} ${PQ_LIB})

#target_link_libraries(test gtest gtest_main)
#target_link_libraries(test -lgmock)
#target_link_libraries(test pthread)