//
// Created by danil on 17.11.2020.
//


#include "gtest/gtest.h"
#include "../Allocator_lib/MemoryAllocator.h"


TEST(AllocatorFixture, allocate16){
    MemoryAllocator allocator;
    allocator.init();

    int* pi2 = (int*)allocator.alloc(16);
    *pi2 = 378;
    EXPECT_EQ(*pi2, 378);
    allocator.free(pi2);
    allocator.destroy();
}

TEST(AllocatorFixture, allocate32){
    MemoryAllocator allocator;
    allocator.init();

    int* pi2 = (int*)allocator.alloc(32);
    *pi2 = 378;
    EXPECT_EQ(*pi2, 378);
    allocator.free(pi2);
    allocator.destroy();
}

TEST(AllocatorFixture, allocate64){
    MemoryAllocator allocator;
    allocator.init();

    int* pi2 = (int*)allocator.alloc(64);
    *pi2 = 378;
    EXPECT_EQ(*pi2, 378);
    allocator.free(pi2);
    allocator.destroy();
}

TEST(AllocatorFixture, allocate128){
    MemoryAllocator allocator;
    allocator.init();

    int* pi2 = (int*)allocator.alloc(128);
    *pi2 = 378;
    EXPECT_EQ(*pi2, 378);
    allocator.free(pi2);
    allocator.destroy();
}

TEST(AllocatorFixture, allocate256){
    MemoryAllocator allocator;
    allocator.init();

    int* pi2 = (int*)allocator.alloc(256);
    *pi2 = 378;
    EXPECT_EQ(*pi2, 378);
    allocator.free(pi2);
    allocator.destroy();
}

TEST(AllocatorFixture, allocate512){
    MemoryAllocator allocator;
    allocator.init();

    int* pi2 = (int*)allocator.alloc(512);
    *pi2 = 378;
    EXPECT_EQ(*pi2, 378);
    allocator.free(pi2);
    allocator.destroy();
}

TEST(AllocatorFixture, allocate10000000){
    MemoryAllocator allocator;
    allocator.init();

    int* pi2 = (int*)allocator.alloc(10000000);
    *pi2 = 378;
    EXPECT_EQ(*pi2, 378);
    allocator.free(pi2);
    allocator.destroy();
}

TEST(AllocatorFixture, allocate20000000){
    MemoryAllocator allocator;
    allocator.init();

    int* pi2 = (int*)allocator.alloc(20000000);
    *pi2 = 378;
    EXPECT_EQ(*pi2, 378);
    allocator.free(pi2);
    allocator.destroy();
}
