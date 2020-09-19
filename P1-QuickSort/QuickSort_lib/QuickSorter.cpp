
#include "QuickSorter.h"

template<typename T, typename Compare>
void /*QuickSorter::*/sort(T *first, T *last, Compare comp)
{
//    while (first < last)
    while(last - first > INSERTION_SORT_THRESHOLD)
    {
        T* pivot = partition<T>(first, last, comp);

        if(pivot - first + 1 < last - pivot){
            sort(pivot + 1, last, comp);
            last = pivot; //tail recursion optimization
        }else{
            sort(first, pivot, comp);
            first = pivot + 1; //tail recursion optimization
        }
    }

    insertionSort(first, last - first + 1, comp); //if only several elements left use insertion sort
}

template<typename T, typename Compare>
void /*QuickSorter::*/insertionSort(T arr[], int n, Compare comp)
{
    T key;
    int i, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
        greater than key, to one position ahead
        of their current position */
        while (j >= 0 && comp(key, arr[j]))
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}


template<typename T, typename Compare>
T* /*QuickSorter::*/partition(T *first, T *last, Compare comp)
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

        //to save actual pivot
        if(pivot == first)
            pivot = last;
        else if(pivot == last)
            pivot = first;

        swap(first, last);
    }
}

template<typename T, typename Compare>
T* /*QuickSorter::*/median(T* a, T* b, T* c, Compare comp)
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
void /*QuickSorter::*/swap(T* a, T* b){
    T temp = *a;
    *a = *b;
    *b = temp;
}
