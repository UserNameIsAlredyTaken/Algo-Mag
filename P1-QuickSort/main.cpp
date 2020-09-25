#include <iostream>
#include "QuickSorter.h"
#include "QuickSorter.cpp"
#include <random>
#include <chrono>
//#include <winnt.h>
#include <windows.h>
#include <profileapi.h>
#include "Google_tests/TestUtils.cpp"


int main() {

    constexpr int sizes[15] = {5, 15, 25, 35, 45, 55, 65, 75, 85,95, 105, 200, 300, 400, 500};
    static const int size = 500;
    int array[size];
    initRandomArr(array, size);

    for(int j = 0; j < sizeof(sizes)/sizeof(sizes[0]); ++j)
    {
        int measurements = 100000;
        int currentSize = sizes[j];
        long double time = 0;
        LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds;
        LARGE_INTEGER Frequency;

        for (int i = 0; i < measurements; i++)
        {
//            shuffleArr(array, currentSize);
            sort(array, array + currentSize - 1, [](int a, int b) { return a > b; });

            QueryPerformanceFrequency(&Frequency);
            QueryPerformanceCounter(&StartingTime);
//            auto start = std::chrono::high_resolution_clock::now();
            insertionSort(array, currentSize, [](int a, int b) { return a < b; });
//            auto end = std::chrono::high_resolution_clock::now();
            QueryPerformanceCounter(&EndingTime);
            ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
            ElapsedMicroseconds.QuadPart *= 1000000;
            ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
            time += ElapsedMicroseconds.QuadPart;

//            time += (end - start).count();
        }
        std::cout << "Insertion = size: " << currentSize << " ;chrono: " << time / measurements << std::endl;
    }

    for(int j = 0; j < sizeof(sizes)/sizeof(sizes[0]); ++j)
    {
        int measurements = 100000;
        int currentSize = sizes[j];
        long double time = 0;
        LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds;
        LARGE_INTEGER Frequency;

        for (int i = 0; i < measurements; i++)
        {
//            shuffleArr(array, currentSize);
            sort(array, array + currentSize - 1, [](int a, int b) { return a > b; });

            QueryPerformanceFrequency(&Frequency);
            QueryPerformanceCounter(&StartingTime);
//            auto start = std::chrono::high_resolution_clock::now();
            sort(array, array + currentSize - 1, [](int a, int b) { return a < b; });
//            auto end = std::chrono::high_resolution_clock::now();
            QueryPerformanceCounter(&EndingTime);
            ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
            ElapsedMicroseconds.QuadPart *= 1000000;
            ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
            time += ElapsedMicroseconds.QuadPart;

//            time += (end - start).count();
        }
        std::cout << "Insertion = size: " << currentSize << " ;chrono: " << time / measurements << std::endl;
    }

    return 0;
}


//sort(array, array + size - 1, [](int a, int b) { return a < b; });
//std::sort(array,array + size - 1);
//insertionSort(array, size, [](int a, int b) { return a < b; });