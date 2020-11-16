//
// Created by danil on 14.11.2020.
//

#include "CoalesceAllocator.h"
#include <iostream>

CoalesceAllocator::CoalesceAllocator(size_t pageSize) : pageSize(pageSize) {}

CoalesceAllocator::~CoalesceAllocator()
{
#ifdef _DEBUG
    assert(bDeinitialized);
#endif
}

void CoalesceAllocator::init() {
#ifdef _DEBUG
    bInitialized = true;
#endif
    pagePointer = AllocatePageFromOS();
}

void CoalesceAllocator::destroy() {
#ifdef _DEBUG
    assert(bInitialized);
    assert(!CheckIfAllocatorHasAllocatedBlock());
#endif

    LPVOID currentIteratedPage = pagePointer;
    while(((PageHeader*)currentIteratedPage)->NextPage != nullptr)
    {
        LPVOID nextPage = ((PageHeader*)currentIteratedPage)->NextPage;
        VirtualFree(currentIteratedPage, 0, MEM_RELEASE);
        currentIteratedPage = nextPage;
    }

    VirtualFree(currentIteratedPage, 0, MEM_RELEASE);

#ifdef _DEBUG
    bDeinitialized = true;
    bInitialized = false;
#endif
}

void *CoalesceAllocator::alloc(size_t requiredSize) {
#ifdef _DEBUG
    assert(bInitialized);
    assert(requiredSize <= pageSize - sizeof(PageHeader) - sizeof(BlockHeader));
#endif
    if(requiredSize < MIN_ALLOCATABLE_SIZE)
        requiredSize = MIN_ALLOCATABLE_SIZE;

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

    LPVOID nextFreeBlock = ((BlockHeader*)allocatedBlock)->nextFreeBlock;
    LPVOID prevFreeBlock = ((BlockHeader*)allocatedBlock)->prevFreeBlock;
    LPVOID nextBlock = ((BlockHeader*)allocatedBlock)->nextBlock;
    LPVOID prevBlock = ((BlockHeader*)allocatedBlock)->prevBlock;
    if(((BlockHeader*)allocatedBlock)->blockSize - requiredSize >= sizeof(BlockHeader) + MIN_ALLOCATABLE_SIZE)////split the block if there is enough space for another one
    {
        LPVOID remainingBlock = (PBYTE)allocatedBlock + requiredSize + sizeof(BlockHeader); ////create new block from left space
        *((BlockHeader*)remainingBlock) = BlockHeader{((BlockHeader*)allocatedBlock)->blockSize - requiredSize - sizeof(BlockHeader),
                                                      prevFreeBlock, nextFreeBlock,
                                                      allocatedBlock, nextBlock,
                                            false};
        ////update allocated block size
        ((BlockHeader*)allocatedBlock)->blockSize = requiredSize;
        ////set new links
        ((BlockHeader*)allocatedBlock)->nextBlock = remainingBlock;
        if(prevFreeBlock)
            ((BlockHeader*)prevFreeBlock)->nextFreeBlock = remainingBlock;
        if(nextFreeBlock)
            ((BlockHeader*)nextFreeBlock)->prevFreeBlock = remainingBlock;
        if(nextBlock)
            ((BlockHeader*)nextBlock)->prevBlock = remainingBlock;

        if(((PageHeader*)currentIteratedPage)->FreeListHead == allocatedBlock) ////if allocated block was free list head set new free list head
            ((PageHeader*)currentIteratedPage)->FreeListHead = remainingBlock;
    }
    else ////allocate whole block
    {
        ////set new links
        if(prevFreeBlock)
            ((BlockHeader*)prevFreeBlock)->nextFreeBlock = nextFreeBlock;
        if(nextFreeBlock)
            ((BlockHeader*)nextFreeBlock)->prevFreeBlock = prevFreeBlock;

        if(((PageHeader*)currentIteratedPage)->FreeListHead == allocatedBlock) ////if allocated block was free list head set new free list head
            ((PageHeader*)currentIteratedPage)->FreeListHead = nextFreeBlock;
    }

    ((BlockHeader*)allocatedBlock)->bAllocated = true;
    return (PBYTE)allocatedBlock + sizeof(BlockHeader);
}

void CoalesceAllocator::free(void *p) {
#ifdef _DEBUG
    assert(bInitialized);
#endif
    p = (PBYTE)p - sizeof(BlockHeader);

    LPVOID currentIteratedPage = pagePointer;
    ////find a page in which the pointer is located
    while(!CheckIfPointerInPage(p, currentIteratedPage, pageSize))
        currentIteratedPage = ((PageHeader*)currentIteratedPage)->NextPage;

    LPVOID p_prev = ((BlockHeader*)p)->prevBlock;
    LPVOID p_next = ((BlockHeader*)p)->nextBlock;
    if(p_prev && !((BlockHeader*)p_prev)->bAllocated)
    {
        if(p_next && !((BlockHeader*)p_next)->bAllocated)
        { ////prev and next are free
            if(((PageHeader*)currentIteratedPage)->FreeListHead == p_next)
                ((PageHeader*)currentIteratedPage)->FreeListHead = p_prev;
            ////link consumed block's next and p->prev to each other
            if((BlockHeader*)((BlockHeader*)p_next)->prevFreeBlock)
                ((BlockHeader*)((BlockHeader*)p_next)->prevFreeBlock)->nextFreeBlock = ((BlockHeader*)p_next)->nextFreeBlock;
            if((BlockHeader*)((BlockHeader*)p_next)->nextFreeBlock)
                ((BlockHeader*)((BlockHeader*)p_next)->nextFreeBlock)->prevFreeBlock = ((BlockHeader*)p_next)->prevFreeBlock;
            ////link p->prev block with p->next->next block
            ((BlockHeader*)p_prev)->nextBlock = ((BlockHeader*)p_next)->nextBlock;
            if((BlockHeader*)((BlockHeader*)p_next)->nextFreeBlock)
                ((BlockHeader*)((BlockHeader*)p_next)->nextFreeBlock)->prevBlock = p_prev;
            ////update size
            ((BlockHeader*)p_prev)->blockSize += ((BlockHeader*)p)->blockSize +((BlockHeader*)p_next)->blockSize + 2 * sizeof(BlockHeader);
        }
        else
        { ////only prev is free
            ((BlockHeader*)p_prev)->nextBlock = p_next;
            if(p_next)
                ((BlockHeader*)p_next)->prevBlock = p_prev;
            ////update size
            ((BlockHeader*)p_prev)->blockSize += ((BlockHeader*)p)->blockSize + sizeof(BlockHeader);
        }
    }
    else
    {
        if(p_next && !((BlockHeader*)p_next)->bAllocated)
        { ////only next is free
            ////fix free list head if needed
            if(((PageHeader*)currentIteratedPage)->FreeListHead == p_next)
                ((PageHeader*)currentIteratedPage)->FreeListHead = p;
            ////link p with p->next->nextFree
            ((BlockHeader*)p)->nextFreeBlock = ((BlockHeader*)p_next)->nextFreeBlock;
            if(((BlockHeader*)p_next)->nextFreeBlock)
                ((BlockHeader*)((BlockHeader*)p_next)->nextFreeBlock)->prevFreeBlock = p;
            ////link p with p->next->prevFree
            ((BlockHeader*)p)->prevFreeBlock = ((BlockHeader*)p_next)->prevFreeBlock;
            if(((BlockHeader*)p_next)->prevFreeBlock)
                ((BlockHeader*)((BlockHeader*)p_next)->prevFreeBlock)->nextFreeBlock = p;
            ////link p with p->next->next
            if(((BlockHeader*)p_next)->nextBlock)
                ((BlockHeader*)((BlockHeader*)p_next)->nextBlock)->prevBlock = p;
            ((BlockHeader*)p)->nextBlock = ((BlockHeader*)p_next)->nextBlock;
            ////update size
            ((BlockHeader*)p)->blockSize += ((BlockHeader*)p_next)->blockSize + sizeof(BlockHeader);
            ////set flag for p
            ((BlockHeader*)p)->bAllocated = false;
        }
        else
        { ////prev and next are not free
            ////set freed block in free list head
            ((BlockHeader*)p)->nextFreeBlock = ((PageHeader*)currentIteratedPage)->FreeListHead;
            if(((PageHeader*)currentIteratedPage)->FreeListHead)
                ((BlockHeader*)((PageHeader*)currentIteratedPage)->FreeListHead)->prevFreeBlock = p;
            ((BlockHeader*)p)->prevFreeBlock = nullptr;
            ((PageHeader*)currentIteratedPage)->FreeListHead = p;
            ((BlockHeader*)p)->bAllocated = false; ////set the flag to false
        }
    }
}

void* CoalesceAllocator::AllocatePageFromOS() const {
    LPVOID newPage = VirtualAlloc(NULL, pageSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE); ////allocate page from OS

    LPVOID freeListHead = (PBYTE)newPage + sizeof(PageHeader);
    *((PageHeader*)newPage) = PageHeader{freeListHead, nullptr}; ////write header to the allocated page

    *((BlockHeader*)freeListHead) = BlockHeader{pageSize - sizeof(PageHeader) - sizeof(BlockHeader),
                                                nullptr, nullptr,
                                                nullptr, nullptr,
                                                false}; ////write header to free list head block
    return newPage;
}

////returns nullptr if there is no any fitted block
void *CoalesceAllocator::FindFirstFit(void *page, size_t size) {
    LPVOID currentIteratedBlock = ((PageHeader*)page)->FreeListHead;

    while(((BlockHeader*)currentIteratedBlock)->blockSize < size)
    {
        if(((BlockHeader*)currentIteratedBlock)->nextFreeBlock == nullptr)
            return nullptr;

        currentIteratedBlock = ((BlockHeader*)currentIteratedBlock)->nextFreeBlock;
    }

    return currentIteratedBlock;
}

bool CoalesceAllocator::CheckIfPageHasAllocatedBlock(void* page)
{
    if(!((PageHeader*)page)->FreeListHead)
        return true;

    ////if free list head has prev or next neighbours
    return ((BlockHeader*)((PageHeader*)page)->FreeListHead)->prevBlock || ((BlockHeader*)((PageHeader*)page)->FreeListHead)->nextBlock;
}

bool CoalesceAllocator::CheckIfAllocatorHasAllocatedBlock()
{
    LPVOID currentIteratedPage = pagePointer;
    while(((PageHeader*)currentIteratedPage)->NextPage != nullptr)
    {
        if(CheckIfPageHasAllocatedBlock(currentIteratedPage))
            return true;

        currentIteratedPage = ((PageHeader*)currentIteratedPage)->NextPage;
    }

    if(CheckIfPageHasAllocatedBlock(currentIteratedPage))
        return true;

    return false;
}

bool CoalesceAllocator::CheckIfPointerIsInsideAllocator(void * p) {
    LPVOID currentIteratedPage = pagePointer;

    while(((PageHeader*)currentIteratedPage)->NextPage != nullptr)
    {
        if(CheckIfPointerInPage(p, currentIteratedPage, pageSize))
            return true;

        currentIteratedPage = ((PageHeader*)currentIteratedPage)->NextPage;
    }

    if(CheckIfPointerInPage(p, currentIteratedPage, pageSize))
        return true;

    return false;
}
