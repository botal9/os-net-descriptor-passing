cmake_minimum_required(VERSION 2.8)

project(os-net-descriptor-passing)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined")

include_directories(${CMAKE_SOURCE_DIR})

add_library(socket-lib
        socket_wrapper.h
        socket_wrapper.cpp)

add_library(pipe-lib
        pipe.h
        pipe.cpp
        message_utils.h)

add_executable(os-net-server
        main-server.cpp
        server.h
        server.cpp)

add_executable(os-net-client
        main-client.cpp
        client.h
        client.cpp)

target_link_libraries(os-net-server
        socket-lib
        pipe-lib)

target_link_libraries(os-net-client
        socket-lib
        pipe-lib)
