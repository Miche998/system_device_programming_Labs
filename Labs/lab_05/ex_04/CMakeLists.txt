cmake_minimum_required(VERSION 3.21)
project(ex_04 C)

set(CMAKE_C_STANDARD 99)

add_executable(ex_04 main.c)
find_package(Threads REQUIRED)
target_link_libraries(ex_04 PRIVATE Threads::Threads)