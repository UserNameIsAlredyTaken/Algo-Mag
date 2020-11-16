//
// Created by danil on 14.11.2020.
//

#ifndef TESTING_TEST_COALESCEALLOCATOR_H
#define TESTING_TEST_COALESCEALLOCATOR_H

#include "windows.h"
#include <cassert>
#include "MemoryAllocator.h"
#include "AllocatorUtil.h"


class CoalesceAllocator { ////TODO: comment all
public:
    explicit CoalesceAllocator(size_t pageSize);
    virtual ~CoalesceAllocator();
    virtual void init();
    virtual void destroy();
    virtual void* alloc(size_t requiredSize);
    virtual void free(void* p);

//private:
    LPVOID pagePointer;
    size_t pageSize;

    void* AllocatePageFromOS() const;
    void* FindFirstFit(void* page, size_t size);

#ifdef _DEBUG
    bool bInitialized;
    bool bDeinitialized;
#endif
};

struct BlockHeader{
    size_t blockSize;
    LPVOID PrevFreeBloc;
    LPVOID NextFreeBlock;
};


#endif //TESTING_TEST_COALESCEALLOCATOR_H
