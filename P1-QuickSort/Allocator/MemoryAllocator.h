//
// Created by danil on 14.11.2020.
//

#ifndef TESTING_TEST_MEMORYALLOCATOR_H
#define TESTING_TEST_MEMORYALLOCATOR_H

#define OS_ALLOCATION_THRESHOLD 10485760

#include "FixedSizeAllocator.h"
#include "CoalesceAllocator.h"


class MemoryAllocator {
public:
    MemoryAllocator();
    virtual ~MemoryAllocator();
    virtual void init();
    virtual void destroy();
    virtual void *alloc(size_t size);
    virtual void free( void *p);

#ifdef _DEBUG
    virtual void dumpStat() const ;
    virtual void dumpBlocks() const ;
#endif


private:
    FixedSizeAllocator fsa16;
    FixedSizeAllocator fsa32;
    FixedSizeAllocator fsa64;
    FixedSizeAllocator fsa128;
    FixedSizeAllocator fsa256;
    FixedSizeAllocator fsa512;
    CoalesceAllocator ca;

#ifdef _DEBUG
    bool bInitialized;
    bool bDeinitialized;

    std::map<LPVOID, size_t> allocatedBlocksStat;
    std::map<LPVOID, size_t> osAllocatedBlocs;
#endif
};








#endif //TESTING_TEST_MEMORYALLOCATOR_H
