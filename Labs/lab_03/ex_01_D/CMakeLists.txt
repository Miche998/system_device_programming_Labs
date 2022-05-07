cmake_minimum_required(VERSION 3.21)
project(ex_01_D C)

set(CMAKE_C_STANDARD 99)

add_executable(ex_01_D main.c)

target_link_libraries(ex_01_D rt)
