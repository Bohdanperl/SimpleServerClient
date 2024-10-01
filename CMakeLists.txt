cmake_minimum_required(VERSION 3.10)
project(ClientServer)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED COMPONENTS system)

add_executable(server server.cpp)
add_executable(client client.cpp)

target_link_libraries(server PRIVATE Boost::system)
target_link_libraries(client PRIVATE Boost::system)

if(UNIX)
    target_link_libraries(server PRIVATE pthread)
    target_link_libraries(client PRIVATE pthread)
endif()

add_custom_command(
    TARGET server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_SOURCE_DIR}/response.txt"
    "$<TARGET_FILE_DIR:server>/response.txt"
)