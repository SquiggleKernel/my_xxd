cmake_minimum_required(VERSION 4.1)
project(my_xxd)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")

add_executable(my_xxd main.cpp
        printAsHex.cpp)
