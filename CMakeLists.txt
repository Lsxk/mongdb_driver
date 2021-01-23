cmake_minimum_required(VERSION 3.17)
project(mongdb_driver)

set(CMAKE_CXX_STANDARD 17)
add_executable(mongdb_driver main.cpp)


find_package(mongocxx REQUIRED)

if (mongocxx_FOUND)
    target_link_libraries(mongdb_driver PRIVATE mongo::mongocxx_shared)
else (mongocxx_FOUND)
    message(FATAL_ERROR "mongocxx library not found")
endif (mongocxx_FOUND)