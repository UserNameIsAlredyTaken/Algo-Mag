cmake_minimum_required(VERSION 3.14)
project(testing_test)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Exception.h Dictionary/Dictionary.cpp Dictionary/Dictionary.h Allocator/MemoryAllocator.cpp Allocator/MemoryAllocator.h Allocator/FixedSizeAllocator.cpp Allocator/FixedSizeAllocator.h Allocator/CoalesceAllocator.cpp Allocator/CoalesceAllocator.h Allocator/AllocatorUtil.cpp Allocator/AllocatorUtil.h)
add_executable(QuickSort_run ${SOURCE_FILES})

include_directories(QuickSort_lib)
include_directories(Containers_lib)
add_subdirectory(QuickSort_lib)
add_subdirectory(Containers_lib)


target_link_libraries(QuickSort_run QuickSort_lib)
target_link_libraries(QuickSort_run Containers_lib)

add_subdirectory(Google_tests)

