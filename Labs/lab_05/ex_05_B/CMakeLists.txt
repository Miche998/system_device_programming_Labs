cmake_minimum_required(VERSION 3.21)
project(ex_05_B C)

set(CMAKE_C_STANDARD 99)

add_executable(ex_05_B main.c)
find_package(Threads REQUIRED)
target_link_libraries(ex_05_B PRIVATE Threads::Threads)