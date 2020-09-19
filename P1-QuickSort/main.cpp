#include <iostream>
#include "QuickSorter.h"
#include "QuickSorter.cpp"
#include <random>
#include <chrono>
#include "Google_tests/TestUtils.cpp"


int main() {

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

//        sort(array, array + size - 1, [](int a, int b) { return a < b; });
        std::sort(array,array + size - 1);
//        insertionSort(array, size, [](int a, int b) { return a < b; });

        auto end = std::chrono::high_resolution_clock::now();
        time += (end - start).count();

        std::cout << "iteration: " << i << std::endl;
    }
    std::cout << "time: " << time << std::endl;
    std::cout << "crono: " << time / measurements << std::endl;

    return 0;
}
