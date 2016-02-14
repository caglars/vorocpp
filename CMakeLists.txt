cmake_minimum_required(VERSION 3.3)
project(vorocpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lvoro++ -Wall -ansi -pedantic -O3 -std=c++11")

include_directories(/usr/local/include/voro++)
link_directories(/usr/local/lib)


set(SOURCE_FILES
        main.cpp
        CSCalculation.cpp CSCalculation.h
        CSSolver.cpp CSSolver.h)

add_executable(vorocpp ${SOURCE_FILES})