cmake_minimum_required(VERSION 3.6)
project(algorithms)

# this is c++11
set(CMAKE_CXX_STANDARD 11)

include_directories( "include" )

set(SOURCE_FILES src/test.cpp include/utility.h include/avl_tree.h include/dectionary.h include/red_black_tree.h)
add_executable(algorithms ${SOURCE_FILES})
