//
// Created by danil on 14.11.2020.
//

#ifndef TESTING_TEST_FIXEDSIZEALLOCATOR_H
#define TESTING_TEST_FIXEDSIZEALLOCATOR_H

#include "windows.h"
#include <cassert>
//#include "MemoryAllocator.h"
#include "AllocatorUtil.h"

class FixedSizeAllocator {
public:
    explicit FixedSizeAllocator(size_t blockSize, size_t pageSize);
    virtual ~FixedSizeAllocator();
    virtual void init();
    virtual void destroy();
    virtual void* alloc();
    virtual void free(void* p);

    bool CheckIfPointerIsInsideAllocator(void* p);
    bool CheckIfAllocatorHasAllocatedBlock();

#ifdef _DEBUG
    void CheckAllocatedAndFreeBlocks(OUT int& allocated, OUT int& free) const;
#endif

private:
    size_t blockSize;
    size_t pageSize;
    LPVOID pagePointer;

    void* AllocatePageFromOS();
    bool CheckIfPageHasAllocatedBlock(void* page);


#ifdef _DEBUG
    bool bInitialized = false;
    bool bDeinitialized = true;
#endif
};


#endif //TESTING_TEST_FIXEDSIZEALLOCATOR_H
