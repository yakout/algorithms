cmake_minimum_required(VERSION 3.6)
project(algorithms)

# this is c++11
set(CMAKE_CXX_STANDARD 11)

include_directories( "include" )

set(SOURCE_FILES src/test.cpp)
add_executable(algorithms ${SOURCE_FILES})
