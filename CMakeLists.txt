cmake_minimum_required(VERSION 4.1)
project(my_xxd)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(my_xxd
    src/main.cpp
    src/core.hpp
)

target_compile_options(my_xxd PRIVATE
    -Wall -Wextra -Wpedantic -Werror
    $<$<CONFIG:Debug>:-fsanitize=address,undefined -fno-omit-frame-pointer>
    $<$<CONFIG:Release>:-O3 -march=native>
)

target_link_options(my_xxd PRIVATE
    $<$<CONFIG:Debug>:-fsanitize=address,undefined>
)