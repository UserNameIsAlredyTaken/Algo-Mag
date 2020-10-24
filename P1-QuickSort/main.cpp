#include <iostream>
#include "QuickSorter.h"
#include "QuickSorter.cpp"
#include <random>
#include <chrono>
//#include <winnt.h>
#include <windows.h>
#include <profileapi.h>
#include "Google_tests/TestUtils.cpp"
#include "Array.h"
#include "Dictionary/Dictionary.h"


int main() {

//    Array<int> arr;
//    std::cout << arr.size();
//
//    arr.insert(1);

//    arr[0] = 3;
//    std::cout << arr[0];
//
//
//    for(int i = 0; i < arr.size(); ++i)
//    {
//        std::cout << arr[i] << std::endl;
//    }






//    constexpr int sizes[15] = {5, 15, 25, 35, 45, 55, 65, 75, 85,95, 105, 200, 300, 400, 500};
//    static const int size = 500;
//    int array[size];
//    initRandomArr(array, size);
//
//    for(int j = 0; j < sizeof(sizes)/sizeof(sizes[0]); ++j)
//    {
//        int measurements = 100000;
//        int currentSize = sizes[j];
//        long double time = 0;
//        LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds;
//        LARGE_INTEGER Frequency;
//
//        for (int i = 0; i < measurements; i++)
//        {
//            sort(array, array + currentSize - 1, [](int a, int b) { return a > b; });
//
//            QueryPerformanceFrequency(&Frequency);
//            QueryPerformanceCounter(&StartingTime);
//            insertionSort(array, currentSize, [](int a, int b) { return a < b; });
//            QueryPerformanceCounter(&EndingTime);
//            ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
//            ElapsedMicroseconds.QuadPart *= 1000000;
//            ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
//            time += ElapsedMicroseconds.QuadPart;
//
//        }
//        std::cout << "Insertion = size: " << currentSize << " ;chrono: " << time / measurements << std::endl;
//    }
//
//    for(int j = 0; j < sizeof(sizes)/sizeof(sizes[0]); ++j)
//    {
//        int measurements = 100000;
//        int currentSize = sizes[j];
//        long double time = 0;
//        LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds;
//        LARGE_INTEGER Frequency;
//
//        for (int i = 0; i < measurements; i++)
//        {
//            sort(array, array + currentSize - 1, [](int a, int b) { return a > b; });
//
//            QueryPerformanceFrequency(&Frequency);
//            QueryPerformanceCounter(&StartingTime);
//            sort(array, array + currentSize - 1, [](int a, int b) { return a < b; });
//            QueryPerformanceCounter(&EndingTime);
//            ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
//            ElapsedMicroseconds.QuadPart *= 1000000;
//            ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
//            time += ElapsedMicroseconds.QuadPart;
//
//        }
//        std::cout << "Insertion = size: " << currentSize << " ;chrono: " << time / measurements << std::endl;
//    }

    Dictionary<std::string, int > npc;
    npc.put("health", 10);
    npc.put("armor", 20);
    npc.put("ammo", 5);
    for ( auto it = npc.iterator(); it.hasNext(); it.next())
        std::cout << it.key() << " " << it.get() << std::endl;

    return 0;
}


//sort(array, array + size - 1, [](int a, int b) { return a < b; });
//std::sort(array,array + size - 1);
//insertionSort(array, size, [](int a, int b) { return a < b; });