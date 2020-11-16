//
// Created by danil on 14.11.2020.
//

#include "CoalesceAllocator.h"
#include <iostream>

CoalesceAllocator::CoalesceAllocator(size_t pageSize) : pageSize(pageSize) {}

CoalesceAllocator::~CoalesceAllocator() {

}

void CoalesceAllocator::init() {
#ifdef _DEBUG
    bInitialized = true;
#endif
    pagePointer = AllocatePageFromOS();
}

void CoalesceAllocator::destroy() {

}

void *CoalesceAllocator::alloc(size_t requiredSize) {
#ifdef _DEBUG
    assert(bInitialized);
#endif
    if(requiredSize < sizeof(BlockHeader))
        requiredSize = sizeof(BlockHeader);

    LPVOID currentIteratedPage = pagePointer;
    LPVOID allocatedBlock = FindFirstFit(currentIteratedPage, requiredSize);
    while(allocatedBlock == nullptr)
    {
        if(((PageHeader*)currentIteratedPage)->NextPage == nullptr)
        {
            ((PageHeader*)currentIteratedPage)->NextPage = AllocatePageFromOS(); ////if there is no page with free block of required size, allocate new page from OS
        }

        currentIteratedPage = ((PageHeader*)currentIteratedPage)->NextPage;
        allocatedBlock = FindFirstFit(currentIteratedPage, requiredSize);
    }

    if(((BlockHeader*)allocatedBlock)->blockSize - requiredSize >= sizeof(BlockHeader))////split the block if there is enough space for another one
    {
        LPVOID remainingBlock = (PBYTE)allocatedBlock + requiredSize;
        LPVOID nextBlock = ((BlockHeader*)allocatedBlock)->NextFreeBlock;
        *((BlockHeader*)remainingBlock) = BlockHeader{((BlockHeader*)allocatedBlock)->blockSize - requiredSize, nullptr, nextBlock};
        ((BlockHeader*)nextBlock)->PrevFreeBloc = remainingBlock;
        ((PageHeader*)currentIteratedPage)->FreeListHead = remainingBlock;
    }
    else ////else just make next block the head of free list
    {
        LPVOID nextBlock = ((BlockHeader*)allocatedBlock)->NextFreeBlock;
        ((BlockHeader*)nextBlock)->PrevFreeBloc = nullptr;
        ((PageHeader*)currentIteratedPage)->FreeListHead = nextBlock;
    }

    return allocatedBlock;
}

void CoalesceAllocator::free(void *p) {
#ifdef _DEBUG
    assert(bInitialized);
#endif

    LPVOID currentIteratedPage = pagePointer;
    ////find a page in which the pointer is located
    while(!CheckIfPointerInPage(p, currentIteratedPage, pageSize))
        currentIteratedPage = ((PageHeader*)currentIteratedPage)->NextPage; ////TODO: continue
}

void* CoalesceAllocator::AllocatePageFromOS() const {
    LPVOID newPage = VirtualAlloc(NULL, pageSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE); ////allocate page from OS

    LPVOID freeListHead = (PBYTE)newPage + sizeof(PageHeader);
    *((PageHeader*)newPage) = PageHeader{freeListHead, nullptr}; ////write header to the allocated page

    *((BlockHeader*)freeListHead) = BlockHeader{pageSize - sizeof(PageHeader), nullptr, nullptr}; ////write header to free list head block


    return newPage;
}

////returns nullptr if there is no any fitted block
void *CoalesceAllocator::FindFirstFit(void *page, size_t size) {
    LPVOID currentIteratedBlock = ((PageHeader*)page)->FreeListHead;

    while(((BlockHeader*)currentIteratedBlock)->blockSize < size)
    {
        if(((BlockHeader*)currentIteratedBlock)->NextFreeBlock == nullptr)
            return nullptr;

        currentIteratedBlock = ((BlockHeader*)currentIteratedBlock)->NextFreeBlock;
    }

    return currentIteratedBlock;
}
