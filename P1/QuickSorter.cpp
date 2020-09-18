
#include "QuickSorter.h"

template<typename T, typename Compare>
void QuickSorter::sort(T *first, T *last, Compare comp)
{
    while (first < last) {
        T* pivot = partition<T>(first, last, comp);

        if(pivot - first < last - pivot){
            sort(pivot + 1, last, comp);
            last = pivot; //tail recursion optimization
        }else{
            sort(first, pivot, comp);
            first = pivot + 1; //tail recursion optimization
        }
    }
}


template<typename T, typename Compare>
T* QuickSorter::partition(T *first, T *last, Compare comp)
{
    T* middle = first + (last - first) / 2;
    T* med = median(first, middle, last, comp);
    swap(middle, med);
    T* pivot = middle;

    while (true)
    {
        while (comp(*first, *pivot))
            first++;

        while(comp(*pivot, *last))
            last--;

        if(first >= last)
            return last;

        swap(first, last);
    }
}

template<typename T, typename Compare>
T* QuickSorter::median(T* a, T* b, T* c, Compare comp)
{
    if (comp(*a, *b))
    {
        if (comp(*b, *c)) // ab ?c
            return b; // abc
        return comp(*a, *c) ? c : a;
    }
    if (comp(*a, *c)) // ba ? c
        return a; // bac
    return comp(*b, *c) ? c : b;
}

template<typename T>
void QuickSorter::swap(T* a, T* b){
    T temp = *a;
    *a = *b;
    *b = temp;
}
