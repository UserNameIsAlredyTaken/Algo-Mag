#include <iostream>

//#include "qsort.h"

template<typename T, typename Compare>
T* median(T* a, T* b, T* c, Compare comp)
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
void swap(T* a, T* b){
    T temp = *a;
    *a = *b;
    *b = temp;
}

template<typename T, typename Compare>
T* partition(T *first, T *last, Compare comp)
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
void sort(T* first, T* last, Compare comp) {

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

int main() {

    int a[5]{1, 2, -3, 756, 99};
    float b[5]{1.9, 2.4, -3, 756.56, 99.7};
    sort(b, b + 4, []( int a, int b) { return a > b; });

    for(int i = 0; i < 5; ++i){
        std::cout << *(b + i) << std::endl;
    }

    return 0;
}
