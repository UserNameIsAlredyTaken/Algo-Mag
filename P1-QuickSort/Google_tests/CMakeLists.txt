project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


add_executable(Google_Tests_run QuickSorterTests.cpp TestUtils.cpp ArrayTest.cpp ListTest.cpp DictionaryTest.cpp AllocatorTest.cpp)

target_link_libraries(Google_Tests_run QuickSort_lib)
target_link_libraries(Google_Tests_run Containers_lib)
target_link_libraries(Google_Tests_run Allocator_lib)

target_link_libraries(Google_Tests_run gtest gtest_main)