set(HEADER_FILES
        Array.h
        )

set(SOURCE_FILES
        Array.cpp List.cpp List.h)

add_library(Containers_lib STATIC
        ${SOURCE_FILES}
        ${HEADER_FILES}
        )