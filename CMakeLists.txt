cmake_minimum_required(VERSION 3.6)
project(algorithms)

set(CMAKE_CXX_STANDARD 11)

include_directories( "include" )

set(SOURCE_FILES src/Heap.cpp include/Heap.h)
add_executable(algorithms ${SOURCE_FILES})
