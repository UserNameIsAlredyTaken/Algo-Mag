#project(DateConverter CXX)

set(HEADER_FILES
        AllocatorUtil.h
        CoalesceAllocator.h
        FixedSizeAllocator.h
        MemoryAllocator.h
        )

set(SOURCE_FILES
        AllocatorUtil.cpp
        CoalesceAllocator.cpp
        FixedSizeAllocator.cpp
        MemoryAllocator.cpp
        )

add_library(Allocator_lib STATIC
        ${SOURCE_FILES}
        ${HEADER_FILES}
        )

#set_target_properties(QuickSort_lib PROPERTIES LINKER_LANGUAGE CXX)