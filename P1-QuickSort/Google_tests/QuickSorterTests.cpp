#include "gtest/gtest.h"
#include "TestUtils.cpp"
#include "QuickSorter.cpp"
#include <numeric>


TEST(QuickSorterFixture, IntTestLess){
    static const int size = 10000;
    int array[size];
    initRandomArr(array, size);
    std::map<int, int> table = initTable(array, size);

    sort(array,array + size - 1, [](int a, int b) { return a < b; });

    EXPECT_EQ(checkArr(array, size, [](int a, int b) { return a < b; }), true);
    EXPECT_EQ(checkTable(array, size, table), true);
}

TEST(QuickSorterFixture, IntTestGreater){
    static const int size = 10000;
    int array[size];
    initRandomArr(array, size);
    std::map<int, int> table = initTable(array, size);

    sort(array,array + size - 1, [](int a, int b) { return a > b; });

    EXPECT_EQ(checkArr(array, size, [](int a, int b) { return a > b; }), true);
    EXPECT_EQ(checkTable(array, size, table), true);
}

TEST(QuickSorterFixture, FloatTestLess){
    static const int size = 10000;
    float array[size];
    initRandomArr(array, size);
    std::map<float, int> table = initTable(array, size);

    sort(array,array + size - 1, [](int a, int b) { return a < b; });

    EXPECT_EQ(checkArr(array, size, [](int a, int b) { return a < b; }), true);
    EXPECT_EQ(checkTable(array, size, table), true);
}

TEST(QuickSorterFixture, FloatTestGreater){
    static const int size = 10000;
    float array[size];
    initRandomArr(array, size);
    std::map<float, int> table = initTable(array, size);

    sort(array,array + size - 1, [](int a, int b) { return a > b; });

    EXPECT_EQ(checkArr(array, size, [](int a, int b) { return a > b; }), true);
    EXPECT_EQ(checkTable(array, size, table), true);
}


