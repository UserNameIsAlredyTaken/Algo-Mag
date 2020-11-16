//
// Created by danil on 14.11.2020.
//

#ifndef TESTING_TEST_FIXEDSIZEALLOCATOR_H
#define TESTING_TEST_FIXEDSIZEALLOCATOR_H

#include <windows.h>
#include <cassert>
#include "MemoryAllocator.h"
#include "AllocatorUtil.h"

class FixedSizeAllocator {
public:
    FixedSizeAllocator(size_t blockSize, size_t pageSize);
    virtual ~FixedSizeAllocator();
    virtual void init();
    virtual void destroy();
    virtual void* alloc();
    virtual void free(void* p);

private:
    size_t blockSize;
    size_t pageSize;
    LPVOID pagePointer;

    void* AllocatePageFromOS();
    bool CheckIfPageHasAllocatedBlock(void* page);
    bool CheckIfAllocatorHasAllocatedBlock();

#ifdef _DEBUG
    bool bInitialized;
    bool bDeinitialized;
#endif
};


#endif //TESTING_TEST_FIXEDSIZEALLOCATOR_H
