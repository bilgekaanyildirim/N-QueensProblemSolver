cmake_minimum_required(VERSION 3.27)
project(N_QuuensProblemSolver)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(N_QuuensProblemSolver
        main.cpp
        stack.cpp
        stack.h)
