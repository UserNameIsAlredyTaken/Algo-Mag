//
// Created by danil on 19.09.2020.
//

#include <map>
#include "QuickSorter.h"

template<typename T, typename Compare>
bool checkArr(T* array, int size, Compare comp)
{
    for(int i = 0; i < size - 1; ++i)
    {
        if(!comp(array[i], array[i + 1]))
            return false;
    }
    return true;
}

template<typename T>
std::map<T, int> initTable(T* array, int size)
{
    std::map<T, int> table;

    for(int i = 0; i < size; ++i)
    {
        if(table.find(array[i]) == table.end()) //if table does not contain the key
        {
            table[array[i]] = 1;
        }
        else
        {
            ++table[array[i]];
        }
    }
    return table;
}

template<typename T>
bool checkTable(T* array, int size, std::map<T, int> table)
{
    for(int i = 0; i < size; ++i)
        --table[array[i]];

    for(auto it=table.begin(); it!=table.end(); ++it)
        if(it->second != 0)
            return false;

    return true;
}

template<typename T>
void shuffleArr(T* array, int size)
{
    for(int i = 0; i < size; ++i)
    {
        static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
        swap(array + i, array + static_cast<int>(rand() * fraction * (size)));
    }
}

template<typename T>
void initRandomArr(T* array, int size)
{
    for(int i = 0; i < size; ++i)
    {
        array[i] = (T)i;
    }

    shuffleArr(array, size);

}