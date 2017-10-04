cmake_minimum_required(VERSION 3.5)
project(moviedb)

set(CMAKE_CXX_STANDARD 11)

add_executable(server Server.cpp)
add_executable(client Client.cpp)
add_executable(client_phase2 Client_printless.cpp)
add_executable(mul_client runMultipleClients.cpp)

target_link_libraries(server mysqlcppconn pthread)
target_link_libraries(mul_client pthread)
target_link_libraries(server)
target_link_libraries(client)
