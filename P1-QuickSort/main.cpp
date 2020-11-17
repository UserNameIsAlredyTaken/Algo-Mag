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
#include "Allocator/FixedSizeAllocator.h"
#include "Allocator/CoalesceAllocator.h"
#include "Allocator/MemoryAllocator.h"


int main() {


//    SYSTEM_INFO sSysInfo;
//    GetSystemInfo(&sSysInfo); ////get page size
//    FixedSizeAllocator fsa(16, sSysInfo.dwPageSize);
//    fsa.init();
//
//    int* pointersArray[511];
//    for(int i = 0; i < 511; i++){
//        pointersArray[i] = (int*)fsa.alloc();
//    }
//    *pointersArray[3] = 58;
//    for(int i = 0; i < 511; i++){
//        fsa.free(pointersArray[i]);
//    }
//
//    *pointersArray[3] = 68;
//
//
//    fsa.destroy();


//    CoalesceAllocator ca(sSysInfo.dwPageSize);
//    ca.init();
//
//    int* pi = (int*)ca.alloc(24);
//    for(int i = 0; i < 6; i++)
//        pi[i] = -1;
//
//    int* pi2 = (int*)ca.alloc(24);
//    for(int i = 0; i < 6; i++)
//        pi2[i] = -1;
//
//    int* pi3 = (int*)ca.alloc(24);
//    for(int i = 0; i < 6; i++)
//        pi3[i] = -1;
//
//    ca.free(pi);
//    ca.free(pi2);
//    ca.free(pi3);
//
//    ca.destroy();


    MemoryAllocator allocator;
    allocator.init();
    int* pi2 = (int*)allocator.alloc(24);
    *pi2 = 378;
//    std::cout << *pi2;
//
    allocator.free(pi2);

#ifdef _DEBUG
    allocator.dumpBlocks();
#endif

    allocator.destroy();

    return 0;
}