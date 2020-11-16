//
// Created by danil on 14.11.2020.
//

#ifndef TESTING_TEST_MEMORYALLOCATOR_H
#define TESTING_TEST_MEMORYALLOCATOR_H



class MemoryAllocator {
public:
    MemoryAllocator();
    virtual ~MemoryAllocator();
    virtual void init();
    virtual void destroy();
    virtual void *alloc(size_t size);
    virtual void free( void *p);
    virtual void dumpStat() const ;
    virtual void dumpBlocks() const ;
};




#endif //TESTING_TEST_MEMORYALLOCATOR_H
