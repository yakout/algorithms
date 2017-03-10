cmake_minimum_required(VERSION 3.6)
project(algorithms)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Heap.cpp Heap.h)
add_executable(algorithms ${SOURCE_FILES})
