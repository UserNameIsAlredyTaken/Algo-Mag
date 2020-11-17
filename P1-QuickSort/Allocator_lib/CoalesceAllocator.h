//
// Created by danil on 14.11.2020.
//

#ifndef TESTING_TEST_COALESCEALLOCATOR_H
#define TESTING_TEST_COALESCEALLOCATOR_H

#include "windows.h"
#include <cassert>
//#include "MemoryAllocator.h"
#include "AllocatorUtil.h"

#define MIN_ALLOCATABLE_SIZE 16


class CoalesceAllocator {
public:
    explicit CoalesceAllocator(size_t pageSize);
    virtual ~CoalesceAllocator();
    virtual void init();
    virtual void destroy();
    virtual void* alloc(size_t requiredSize);
    virtual void free(void* p);

    bool CheckIfPointerIsInsideAllocator(void * p);
    bool CheckIfAllocatorHasAllocatedBlock();

#ifdef _DEBUG
    void CheckAllocatedAndFreeBlocks(OUT int& allocated, OUT int& free) const;
#endif

private:
    LPVOID pagePointer;
    size_t pageSize;

    void* AllocatePageFromOS() const;
    void* FindFirstFit(void* page, size_t size);
    bool CheckIfPageHasAllocatedBlock(void* page);

#ifdef _DEBUG
    bool bInitialized = true;
    bool bDeinitialized = false;
#endif
};

struct BlockHeader{
    size_t blockSize;
    LPVOID prevFreeBlock;
    LPVOID nextFreeBlock;
    LPVOID prevBlock;
    LPVOID nextBlock;
    bool bAllocated; ////to check if could be merged without iterating through whole free list
};


#endif //TESTING_TEST_COALESCEALLOCATOR_H
