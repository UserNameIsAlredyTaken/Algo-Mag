cmake_minimum_required(VERSION 3.14)
project(testing_test)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)
add_executable(QuickSort_run ${SOURCE_FILES})

include_directories(QuickSort_lib)
add_subdirectory(QuickSort_lib)

target_link_libraries(QuickSort_run QuickSort_lib)

add_subdirectory(Google_tests)

