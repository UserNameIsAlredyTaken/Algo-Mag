#include "gtest/gtest.h"
//#include "QuickSorter.h"
#include "QuickSorter.cpp"
#include <random>
#include <chrono>

#include <iostream>
#include <vector>
#include <numeric>
//#include <chrono>

template<typename T>
void initRandomArr(T*& array, int size)
{
    array = new T[size];
    for(int i = 0; i < size; ++i)
    {
        array[i] = (T)i;
    }

    for(int i = 0; i < size; ++i)
    {
        static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
        swap(array + i, array + static_cast<int>(rand() * fraction * (size)));
    }
}

template<typename T, typename Compare>
bool checkArr(T* array, int size, Compare comp)
{
    for(int i = 0; i < size - 1; ++i)
    {
        if(!comp(array[i], array[i + 1]))
            return false;
    }
    return true;
}

template<typename T>
std::map<T, int> initTable(T* array, int size)
{
    std::map<T, int> table;

    for(int i = 0; i < size; ++i)
    {
        if(table.find(array[i]) == table.end()) //if table does not contain the key
        {
            table[array[i]] = 1;
        }
        else
        {
            ++table[array[i]];
        }
    }
    return table;
}

template<typename T>
bool checkTable(T* array, int size, std::map<T, int> table)
{
    for(int i = 0; i < size; ++i)
        --table[array[i]];

    for(auto it=table.begin(); it!=table.end(); ++it)
        if(it->second != 0)
            return false;

    return true;
}


//class QuickSorterFixture : public ::testing::Test {
//
//protected:
//    virtual void SetUp()
//    {
//        sorter = new QuickSorter();
//    }
//
//    virtual void TearDown() {
//        delete sorter;
//    }
//
//    QuickSorter * sorter;
//};

//TEST_F(QuickSorterFixture, IntTest){

TEST(QuickSorterFixture, IntTestLess){
    int size = 10000;
    int* array;
    initRandomArr(array, size);
    std::map<int, int> table = initTable(array, size);

    sort(array,array + size - 1, [](int a, int b) { return a < b; });

    EXPECT_EQ(checkArr(array, size, [](int a, int b) { return a < b; }), true);
    EXPECT_EQ(checkTable(array, size, table), true);
}

TEST(QuickSorterFixture, IntTestGreater){
    int size = 10000;
    int* array;
    initRandomArr(array, size);
    std::map<int, int> table = initTable(array, size);

    sort(array,array + size - 1, [](int a, int b) { return a > b; });

    EXPECT_EQ(checkArr(array, size, [](int a, int b) { return a > b; }), true);
    EXPECT_EQ(checkTable(array, size, table), true);
}

TEST(QuickSorterFixture, FloatTestLess){
    int size = 10000;
    int* array;
    initRandomArr(array, size);
    std::map<int, int> table = initTable(array, size);

    sort(array,array + size - 1, [](int a, int b) { return a < b; });

    EXPECT_EQ(checkArr(array, size, [](int a, int b) { return a < b; }), true);
    EXPECT_EQ(checkTable(array, size, table), true);
}

TEST(QuickSorterFixture, FloatTestGreater){
    int size = 10000;
    float* array;
    initRandomArr(array, size);
    std::map<float, int> table = initTable(array, size);

    sort(array,array + size - 1, [](int a, int b) { return a > b; });

    EXPECT_EQ(checkArr(array, size, [](int a, int b) { return a > b; }), true);
    EXPECT_EQ(checkTable(array, size, table), true);
}

TEST(QuickSorterFixture, TestTime){
    int measurements = 1000;
    int size = 100000;
//    int size = 10;
//    int array[10] = {0,9,4,3,7,1,2,8,6,5};
    int* array;
    initRandomArr(array, size);

    long double time = 0;

    for (int i = 0; i < measurements; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();

        sort(array, array + size - 1, [](int a, int b) { return a < b; });
//        std::sort(array,array + size - 1);
//        insertionSort(array, size, [](int a, int b) { return a < b; });

        auto end = std::chrono::high_resolution_clock::now();
        time += (end - start).count();

        std::cout << "iteration: " << i << std::endl;
    }
    std::cout << "time: " << time << std::endl;
    std::cout << "crono: " << time / measurements << std::endl;
}

