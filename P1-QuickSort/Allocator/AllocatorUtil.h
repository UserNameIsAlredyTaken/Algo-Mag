//
// Created by danil on 15.11.2020.
//

#ifndef TESTING_TEST_ALLOCATORUTIL_H
#define TESTING_TEST_ALLOCATORUTIL_H


#include "windows.h"

struct PageHeader{
    LPVOID FreeListHead;
    LPVOID NextPage;
};


bool CheckIfPointerInPage(void* pointer, void* page, size_t pageSize);

#endif //TESTING_TEST_ALLOCATORUTIL_H
