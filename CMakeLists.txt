cmake_minimum_required(VERSION 3.3)
project(vorocpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories("/Users/caglars/Dropbox/caglars/Programming/Voro++/src")

set(SOURCE_FILES main.cpp)
add_executable(vorocpp ${SOURCE_FILES})