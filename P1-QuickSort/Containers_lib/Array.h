//
// Created by danil on 25.09.2020.
//
#include <utility>
#include "../Exception.h"

#define INITIAL_SIZE 16
#define CAPACITY_MUL 2

#ifndef TESTING_TEST_ARRAY_H
#define TESTING_TEST_ARRAY_H

template < typename T>
class Array final{

private:

    T* array;
    int length; //number of elements in array
    int capacity; //real length


    class Iterator{
    private:
        int current_index;
        Array<T>* iterated;

    public:
        Iterator(Array<T>* iterated) : iterated(iterated), current_index(0){}

        const T& get() const ;
        void set( const T& value);
        void insert( const T& value);
        void remove();
        void next();
        void prev();
        void toIndex( int index);
        bool hasNext() const ;
//        bool hasNoNext() const ;
        bool hasPrev() const ;
//        bool isLast() const ;
//        bool isFirst() const ;
    };

    void redistribute();

public:
    Array();
    Array(int capacity);
    Array(const Array<T>& copiedArr);
    ~Array();
    Array<T>& operator=(const Array<T> & source);


    void insert( const T& value);
    void insert( int index, const T& value);
    void remove( int index);
    const T& operator []( int index) const ;
    T& operator []( int index);
    int size() const ;
    Iterator iterator();
    const Iterator iterator() const ;


};

template<typename T>
void Array<T>::redistribute(){
    capacity *= CAPACITY_MUL;
    T* tempArr = new T[capacity];
    for(int i = 0; i < length; ++i)
    {
        tempArr[i] = std::move(array[i]);
    }
    delete[] array;
    array = tempArr;
}


template<typename T>
Array<T>::Array() : Array<T>::Array(INITIAL_SIZE){}

template<typename T>
Array<T>::Array(int capacity)
{
    array = new T[capacity];
    this->capacity = capacity;
    length = 0;

}

template<typename T>
Array<T>::~Array()
{
    delete[] array;
    array = 0;
}

template<typename T>
Array<T>::Array(const Array<T> &copiedArr)
{
    length = copiedArr.length;
    capacity = copiedArr.capacity;

    if(copiedArr.array)
    {
        array = new T[capacity];

        for(int i = 0; i < capacity; ++i)
        {
            array[i] = copiedArr.array[i];
        }
    }
    else
    {
        array = 0;
    }
}

template<typename T>
Array<T> &Array<T>::operator=(const Array<T> &source) {

    if (this == &source)
        return *this;

    delete[] array;

    length = source.length;
    capacity = source.capacity;

    if(source.array)
    {
        array = new T[capacity];

        for(int i = 0; i < capacity; ++i)
        {
            array[i] = source.array[i];
        }
    }
    else
    {
        array = 0;
    }

    return *this;
}


template<typename T>
void Array<T>::insert(int index, const T &value) {
    if(index > length)
    {
        throw Exception("insertion index is more then array length");
    }

    if(length + 1 > capacity)
    {
        redistribute();
    }

    for (int i = length; i > index; --i) ////move elements to make space for new element
    {
        array[i] = std::move(array[i - 1]);
    }

    array[index] = value;
    ++length;
}

template<typename T>
void Array<T>::insert(const T &value)
{
    insert(length, value);
}

template<typename T>
int Array<T>::size() const
{
    return length;
}

template<typename T>
const T& Array<T>::operator []( int index) const
{
    if(index >= length) throw Exception("index is more then length");
    return array[index];
}

template<typename T>
T& Array<T>::operator []( int index){
    if(index >= length)
    {
        throw Exception("index is more then length");
    }
    return array[index];
}

template<typename T>
void Array<T>::remove( int index){
    if(index > length)
    {
        throw Exception("insertion index is more then array length");
    }

    for (int i = index; i < length; ++i) ////move elements to make space for new element
    {
        array[i] = std::move(array[i + 1]);
    }

    --length;
}
template<typename T>
typename Array<T>::Iterator Array<T>::iterator(){
    Iterator it(this);
    return it;
}

template<typename T>
const typename Array<T>::Iterator Array<T>::iterator() const
{
    Iterator it(this);
    return it;
}

template<typename T>
const T& Array<T>::Iterator::get() const{
    return (*iterated)[current_index];
}

template<typename T>
void Array<T>::Iterator::set( const T& value){
    (*iterated)[current_index] = value;
}

template<typename T>
void Array<T>::Iterator::insert( const T& value)
{
    iterated->insert(current_index, value);
}

template<typename T>
void Array<T>::Iterator::remove()
{
    iterated->remove(current_index);
}

template<typename T>
void Array<T>::Iterator::next()
{
    if(hasNext())
    {
        ++current_index;
    }
    else
    {
        throw Exception("iterator points on last element");
    }
}

template<typename T>
void Array<T>::Iterator::prev()
{
    if(hasPrev())
    {
        --current_index;
    }
    else
    {
        throw Exception("iterator points on first element");
    }
}

template<typename T>
void Array<T>::Iterator::toIndex( int index)
{
    if(index >= 0 && index < iterated->length)
    {
        current_index = index;
    }
    else
    {
        throw Exception("index not in bounds");
    }
}


////changed hasNext and nahPrev to isLast and isFirst
template<typename T>
bool Array<T>::Iterator::hasNext() const
{
    return current_index < iterated->length - 1;
}

template<typename T>
bool Array<T>::Iterator::hasPrev() const
{
    return current_index >= 1;
}

//template<typename T>
//bool Array<T>::Iterator::isLast() const
//{
//    return current_index == iterated->length - 1;
//}
//
//template<typename T>
//bool Array<T>::Iterator::isFirst() const
//{
//    return current_index == 0;
//}
//
//template<typename T>
//bool Array<T>::Iterator::hasNoNext() const
//{
//    return current_index >= iterated->length;
//}



#endif //TESTING_TEST_ARRAY_H