//
// Created by danil on 14.11.2020.
//

#include "MemoryAllocator.h"

MemoryAllocator::MemoryAllocator() : fsa16(16, 4096),
                                     fsa32(32, 4096 * 2),
                                     fsa64(65, 4096 * 4),
                                     fsa128(128, 4096 * 8),
                                     fsa256(256, 4096 * 16),
                                     fsa512(512, 4096 * 32),
                                     ca(1000000 * 10 + sizeof(PageHeader) + sizeof(BlockHeader)) ////page size is 10 Mb + space required for headers
                                     {}

MemoryAllocator::~MemoryAllocator()
{
#ifdef _DEBUG
    assert(bDeinitialized);
#endif
}

void MemoryAllocator::init() {
#ifdef _DEBUG
    bInitialized = true;
    bDeinitialized = false;
#endif
    fsa16.init();
    fsa32.init();
    fsa64.init();
    fsa128.init();
    fsa256.init();
    fsa512.init();
    ca.init();
}

void MemoryAllocator::destroy() {
#ifdef _DEBUG
    assert(bInitialized);
#endif
    fsa16.destroy();
    fsa32.destroy();
    fsa64.destroy();
    fsa128.destroy();
    fsa256.destroy();
    fsa512.destroy();
    ca.destroy();
#ifdef _DEBUG
    bDeinitialized = true;
    bInitialized = false;
#endif
}

void *MemoryAllocator::alloc(size_t size) {
#ifdef _DEBUG
    assert(bInitialized);
#endif
    LPVOID allocatedBLock;

    if(size <= 16){
        allocatedBLock = fsa16.alloc();
#ifdef _DEBUG
        allocatedBlocksStat.insert({allocatedBLock, size});
#endif
        return allocatedBLock;
    }

    if(size <= 32){
        allocatedBLock = fsa32.alloc();
#ifdef _DEBUG
        allocatedBlocksStat.insert({allocatedBLock, size});
#endif
        return allocatedBLock;
    }

    if(size <= 64){
        allocatedBLock = fsa64.alloc();
#ifdef _DEBUG
        allocatedBlocksStat.insert({allocatedBLock, size});
#endif
        return allocatedBLock;
    }

    if(size <= 128){
        allocatedBLock = fsa128.alloc();
#ifdef _DEBUG
        allocatedBlocksStat.insert({allocatedBLock, size});
#endif
        return allocatedBLock;
    }

    if(size <= 256){
        allocatedBLock = fsa256.alloc();
#ifdef _DEBUG
        allocatedBlocksStat.insert({allocatedBLock, size});
#endif
        return allocatedBLock;
    }

    if(size <= 512){
        allocatedBLock = fsa512.alloc();
#ifdef _DEBUG
        allocatedBlocksStat.insert({allocatedBLock, size});
#endif
        return allocatedBLock;
    }

    if(size <= 10000000){
        allocatedBLock = ca.alloc(size);
#ifdef _DEBUG
        allocatedBlocksStat.insert({allocatedBLock, size});
#endif
        return allocatedBLock;
    }

    allocatedBLock = VirtualAlloc(NULL, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
#ifdef _DEBUG
    allocatedBlocksStat.insert({allocatedBLock, size});
    osAllocatedBlocs.insert({allocatedBLock, size});
#endif

    return allocatedBLock;
}

void MemoryAllocator::free(void *p) {
#ifdef _DEBUG
    assert(bInitialized);
    allocatedBlocksStat.erase(p);
#endif
    if(fsa16.CheckIfPointerIsInsideAllocator(p))
    {
        fsa16.free(p);
        return;
    }
    if(fsa32.CheckIfPointerIsInsideAllocator(p))
    {
        fsa32.free(p);
        return;
    }
    if(fsa64.CheckIfPointerIsInsideAllocator(p))
    {
        fsa64.free(p);
        return;
    }
    if(fsa128.CheckIfPointerIsInsideAllocator(p))
    {
        fsa128.free(p);
        return;
    }
    if(fsa256.CheckIfPointerIsInsideAllocator(p))
    {
        fsa256.free(p);
        return;
    }
    if(fsa512.CheckIfPointerIsInsideAllocator(p))
    {
        fsa512.free(p);
        return;
    }
    if(ca.CheckIfPointerIsInsideAllocator(p))
    {
        ca.free(p);
        return;
    }
#ifdef _DEBUG
    osAllocatedBlocs.erase(p);
#endif
    VirtualFree(p, 0, MEM_RELEASE);
}
#ifdef _DEBUG
void MemoryAllocator::dumpStat() const {
    assert(bInitialized);
    int allocatedCount = 0, freeCount = 0;
    fsa16.CheckAllocatedAndFreeBlocks(allocatedCount, freeCount);
    fsa32.CheckAllocatedAndFreeBlocks(allocatedCount, freeCount);
    fsa64.CheckAllocatedAndFreeBlocks(allocatedCount, freeCount);
    fsa128.CheckAllocatedAndFreeBlocks(allocatedCount, freeCount);
    fsa256.CheckAllocatedAndFreeBlocks(allocatedCount, freeCount);
    fsa512.CheckAllocatedAndFreeBlocks(allocatedCount, freeCount);
    ca.CheckAllocatedAndFreeBlocks(allocatedCount, freeCount);

    std::cout << "All allocated blocks count: " << allocatedCount << ", All free blocks: " << freeCount << std::endl;
    std::cout << "OS allocated blocks: " << std::endl;
    for(auto& [address, size] : osAllocatedBlocs){
        std::cout << "Block address: " << address << ", size: " << size << std::endl;
    }
}
#endif

#ifdef _DEBUG
void MemoryAllocator::dumpBlocks() const {
    assert(bInitialized);

    if(allocatedBlocksStat.size() == 0)
        std::cout << "No allocated blocks";
    else
    {
        for(auto& [address, size] : allocatedBlocksStat){
            std::cout << "Block address: " << address << ", size: " << size << std::endl;
        }
    }

}
#endif
