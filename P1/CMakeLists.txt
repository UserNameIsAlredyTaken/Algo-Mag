cmake_minimum_required(VERSION 3.17)
project(P1)

set(CMAKE_CXX_STANDARD 14)

set(HEADER_FILES
        QuickSorter.h
        )

set(SOURCE_FILES
        QuickSorter.cpp
        )

add_executable(P1 main.cpp)

add_subdirectory(Google_tests)