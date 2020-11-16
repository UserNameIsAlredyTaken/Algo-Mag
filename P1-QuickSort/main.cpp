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


int main() {

    SYSTEM_INFO sSysInfo;
    GetSystemInfo(&sSysInfo); ////get page size
    FixedSizeAllocator fsa(16, sSysInfo.dwPageSize);
    fsa.init();

    int* pointersArray[511];
    for(int i = 0; i < 511; i++){
        pointersArray[i] = (int*)fsa.alloc();
    }

    for(int i = 0; i < 511; i++){
        fsa.free(pointersArray[i]);
    }



    fsa.destroy();


    CoalesceAllocator ca(sSysInfo.dwPageSize);
    ca.init();

    int* pi= (int*)ca.FindFirstFit(ca.pagePointer, 5000);


    return 0;
}