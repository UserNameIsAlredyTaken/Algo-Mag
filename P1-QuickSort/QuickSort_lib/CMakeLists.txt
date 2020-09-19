project(DateConverter CXX)




set(HEADER_FILES
        QuickSorter.h
#        QuickSorter.cpp
        )

set(SOURCE_FILES
#        QuickSorter.inl
        QuickSorter.cpp
        )

add_library(QuickSort_lib STATIC
        ${SOURCE_FILES}
        ${HEADER_FILES}
        )

#set_target_properties(QuickSort_lib PROPERTIES LINKER_LANGUAGE CXX)