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

MemoryAllocator::~MemoryAllocator() {

}

void MemoryAllocator::init() {
#ifdef _DEBUG
    bInitialized = true;
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

}

void *MemoryAllocator::alloc(size_t size) {
#ifdef _DEBUG
    assert(bInitialized);
#endif
    if(size <= 16)
        return fsa16.alloc();
    if(size <= 32)
        return fsa32.alloc();
    if(size <= 64)
        return fsa64.alloc();
    if(size <= 128)
        return fsa128.alloc();
    if(size <= 256)
        return fsa256.alloc();
    if(size <= 512)
        return fsa512.alloc();
    if(size <= 100000 * 10)
        return ca.alloc(size);

    return VirtualAlloc(NULL, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
}

void MemoryAllocator::free(void *p) {
#ifdef _DEBUG
    assert(bInitialized);
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
    VirtualFree(p, 0, MEM_RELEASE);
}

void MemoryAllocator::dumpStat() const {
#ifdef _DEBUG
    assert(bInitialized);
#endif

}

void MemoryAllocator::dumpBlocks() const {
#ifdef _DEBUG
    assert(bInitialized);
#endif

}
