//
// Created by danil on 15.11.2020.
//

#include "AllocatorUtil.h"

bool CheckIfPointerInPage(void* pointer, void* page, size_t pageSize)
{
    return page < pointer && pointer < (PBYTE)page + pageSize;
}