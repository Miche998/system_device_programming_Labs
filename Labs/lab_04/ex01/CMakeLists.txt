cmake_minimum_required(VERSION 3.21)
project(ex01 C)

set(CMAKE_C_STANDARD 99)

add_executable(ex01 main.c)
target_link_libraries(ex01 PRIVATE m)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(ex01 PRIVATE Threads::Threads)