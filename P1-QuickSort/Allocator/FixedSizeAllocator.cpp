//
// Created by danil on 14.11.2020.
//

#include "FixedSizeAllocator.h"



FixedSizeAllocator::FixedSizeAllocator(size_t blockSize, size_t pageSize) : pageSize(pageSize), blockSize(blockSize) {}

void* FixedSizeAllocator::alloc() {
#ifdef _DEBUG
    assert(bInitialized);
#endif
    LPVOID allocatedBlock;
    LPVOID currentIteratedPage = pagePointer;

    ////iterate through all accessible pages checking if there is a free block
    while(((PageHeader*)currentIteratedPage)->FreeListHead == nullptr)
    {
        if(((PageHeader*)currentIteratedPage)->NextPage == nullptr)
        {
            ((PageHeader*)currentIteratedPage)->NextPage = AllocatePageFromOS(); ////if there is no page with free block, allocate new page from OS
        }

        currentIteratedPage = ((PageHeader*)currentIteratedPage)->NextPage;
    }

    allocatedBlock = ((PageHeader*)currentIteratedPage)->FreeListHead; ////get allocated block from page's free list head
    ((PageHeader*)currentIteratedPage)->FreeListHead = (LPVOID)(*((PDWORD)allocatedBlock)); ////write new free list head

    return allocatedBlock;
}

void FixedSizeAllocator::init() {
#ifdef _DEBUG
    bInitialized = true;
#endif
    pagePointer = AllocatePageFromOS();
}

FixedSizeAllocator::~FixedSizeAllocator()
{
#ifdef _DEBUG
    assert(bDeinitialized);
#endif
}

void FixedSizeAllocator::destroy()
{
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

void FixedSizeAllocator::free(void* p)
{
#ifdef _DEBUG
    assert(bInitialized);
#endif

    LPVOID currentIteratedPage = pagePointer;
    ////find a page in which the pointer is located
    while(!CheckIfPointerInPage(p, currentIteratedPage, pageSize))
        currentIteratedPage = ((PageHeader*)currentIteratedPage)->NextPage;

    *((PVOID*)p) = ((PageHeader*)currentIteratedPage)->FreeListHead;
    ((PageHeader*)currentIteratedPage)->FreeListHead = (PVOID)p;
}

void* FixedSizeAllocator::AllocatePageFromOS() {
    LPVOID newPage = VirtualAlloc(NULL, pageSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE); ////allocate page from OS
    *((PageHeader*)newPage) = PageHeader{(PBYTE)newPage + sizeof(PageHeader), nullptr}; ////write header to the allocated page
    ////mark up the page into equal sized blocks
    for(int i = 0; i < ((pageSize - sizeof(PageHeader)) / blockSize) - 1; i++)
    {
        *((LPVOID*)((PBYTE)newPage + sizeof(PageHeader) + blockSize * i)) = (LPVOID*)((PBYTE)newPage + sizeof(PageHeader) + blockSize * (i + 1));
    }
    *((LPVOID*)((PBYTE)newPage + sizeof(PageHeader) + blockSize * ((pageSize - sizeof(PageHeader)) / blockSize))) = nullptr;

    return newPage;
}

bool FixedSizeAllocator::CheckIfPageHasAllocatedBlock(void* page)
{
    LPVOID currentIteratedBlock = ((PageHeader*)page)->FreeListHead;
    for(int i = 0; i < ((pageSize - sizeof(PageHeader)) / blockSize); i++)
    {
        if(currentIteratedBlock == nullptr)
            return true;

        currentIteratedBlock = (LPVOID)(*((PDWORD)currentIteratedBlock));
    }

    return false;
}

bool FixedSizeAllocator::CheckIfAllocatorHasAllocatedBlock()
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
