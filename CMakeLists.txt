cmake_minimum_required(VERSION 3.10)
project(test_zmq_pipeline VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(inc)

# add cpp flags
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g -O3  -Wall -Werror")


add_executable(zmq_pusher_client
        src/client.cpp)

add_executable(zmq_puller_server
        src/server.cpp)

target_link_libraries(zmq_pusher_client
        zmq)

target_link_libraries(zmq_puller_server
        zmq)
