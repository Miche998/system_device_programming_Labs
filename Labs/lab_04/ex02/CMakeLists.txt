cmake_minimum_required(VERSION 3.21)
project(ex02 C)

set(CMAKE_C_STANDARD 99)

add_executable(ex02 main.c)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(ex02 PRIVATE Threads::Threads)
