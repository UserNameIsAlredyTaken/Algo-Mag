#define INSERTION_SORT_THRESHOLD 5000

//
//class QuickSorter{
//public:
//    template<typename T, typename Compare>
//    void sort(T* first, T* last, Compare comp);
//
//private:
//    template<typename T, typename Compare>
//    T* partition(T *first, T *last, Compare comp);
//
//    template<typename T>
//    void swap(T* a, T* b);
//
//    template<typename T, typename Compare>
//    T* median(T* a, T* b, T* c, Compare comp);
//};

template<typename T, typename Compare>
void sort(T* first, T* last, Compare comp);


template<typename T, typename Compare>
T* partition(T *first, T *last, Compare comp);

template<typename T>
void swap(T* a, T* b);

template<typename T, typename Compare>
T* median(T* a, T* b, T* c, Compare comp);

template<typename T, typename Compare>
void insertionSort(T arr[], int n, Compare comp);

