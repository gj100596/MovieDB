cmake_minimum_required(VERSION 3.8)
project(moviedb)

set(CMAKE_CXX_STANDARD 11)


set(SOURCE_FILES main.cpp Classes.cpp)
add_executable(moviedb ${SOURCE_FILES})

add_executable(server Server.cpp)
add_executable(client Client.cpp)

target_link_libraries(moviedb mysqlcppconn pthread)
target_link_libraries(server mysqlcppconn pthread)