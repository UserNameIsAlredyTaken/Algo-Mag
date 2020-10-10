//
// Created by danil on 26.09.2020.
//

#ifndef TESTING_TEST_LIST_H
#define TESTING_TEST_LIST_H


#include "../Exception.h"
#include "Array.h"
#define MAX_CHUNK_LENGTH 8

template < typename T>
class List final {

private:

    class Chunk{
    public:
        Chunk(){
            next = nullptr;
            prev = nullptr;
        }
//        Chunk(const T& value){
//            this->value = value;
//            next = nullptr;
//            prev = nullptr;
//        }

        Array<T> array;
        Chunk* next;
        Chunk* prev;
    };

    class Iterator{
//TODO:    private:
    public:
        List<T>* iterated;
        Chunk* current_chunk;
        int current_index;

    public:
        Iterator(List<T>* iterated) : iterated(iterated), current_chunk(iterated->tail_chunk), current_index(0){}

        const T& get() const ;
        void set( const T& value);
        void insert( const T& value);
        void remove();
        void next();
        void prev();
        bool hasNext() const ;
        bool hasPrev() const ;
    };

    Chunk* head_chunk;
    Chunk* tail_chunk;

    int length;

public:
    List();
    ~List();

    void insertHead( const T& value);
    void insertTail( const T& value);
    void removeHead();
    void removeTail();
    const T& head() const ;
    const T& tail() const ;
    int size() const ;
    Iterator iterator();
    const Iterator iterator() const ;
};

template<typename T>
List<T>::List() : head_chunk(nullptr), tail_chunk(nullptr), length(0)
{
    Chunk* chunk = new Chunk();
    head_chunk = chunk;
    tail_chunk = chunk;
}

template<typename T>
List<T>::~List(){
    while(head_chunk->prev){
        removeHead();
    }
    delete head_chunk;
    head_chunk = nullptr;
    tail_chunk = nullptr;
}


template<typename T>
void List<T>::insertHead( const T& value)
{
    if(head_chunk->array.size() < MAX_CHUNK_LENGTH)
    {
        head_chunk->array.insert(value);
    }
    else
    {
        Chunk* chunk = new Chunk();
        chunk->array.insert(value);

        chunk->prev = head_chunk;
        head_chunk->next = chunk;
        head_chunk = chunk;
    }
    ++length;
}

template<typename T>
void List<T>::insertTail(const T &value)
{

    if(tail_chunk->array.size() < MAX_CHUNK_LENGTH)
    {
        tail_chunk->array.insert(0, value);
    }
    else
    {
        Chunk* chunk = new Chunk();
        chunk->array.insert(0, value);

        chunk->next = tail_chunk;
        tail_chunk->prev = chunk;
        tail_chunk = chunk;
    }
    ++length;
}

template<typename T>
void List<T>::removeHead()
{
    head_chunk->array.remove(head_chunk->array.size() - 1);
    if(head_chunk->array.size() == 0 && head_chunk->prev) ////do not delete last
    {
        head_chunk = head_chunk->prev;
        delete head_chunk->next;
        head_chunk->next = nullptr;
    }

    --length;
}

template<typename T>
void List<T>::removeTail()
{
    tail_chunk->array.remove(0);
    if(tail_chunk->array.size() == 0 && tail_chunk->next)////do not delete last
    {
        tail_chunk = tail_chunk->next;
        delete tail_chunk->prev;
        tail_chunk->prev = nullptr;
    }

    --length;
}

template<typename T>
const T& List<T>::head() const
{
    return head_chunk->array[head_chunk->array.size() - 1];
}

template<typename T>
const T& List<T>::tail() const
{
    return tail_chunk->array[0];
}

template<typename T>
int List<T>::size() const
{
    return length;
}

template<typename T>
typename List<T>::Iterator List<T>::iterator(){
    Iterator it(this);
    return it;
}

template<typename T>
const typename List<T>::Iterator List<T>::iterator() const
{
    Iterator it(this);
    return it;
}

template<typename T>
const T& List<T>::Iterator::get() const
{
    return current_chunk->array[current_index];
}

template<typename T>
void List<T>::Iterator::set( const T& value){
    current_chunk->array[current_index] = value;
}

template<typename T>
void List<T>::Iterator::insert( const T& value)
{
    current_chunk->array.insert(current_index, value);
    if(current_chunk->array.size() > MAX_CHUNK_LENGTH - 1)
    {
        Chunk* chunk = new Chunk();
        chunk->array.insert(current_chunk->array[MAX_CHUNK_LENGTH - 1]); ////move last element of current chunk
        current_chunk->array.remove(MAX_CHUNK_LENGTH - 1); ////to new chunk

        chunk->prev = current_chunk;
        chunk->next = current_chunk->next;
        if(current_chunk->next)
            current_chunk->next->prev = chunk;
        current_chunk->next = chunk;

        if(iterated->head_chunk == current_chunk)
            iterated->head_chunk = chunk;
    }
    this->next();
    ++iterated->length;
}

template<typename T>
void List<T>::Iterator::remove()
{
    current_chunk->array.remove(current_index);
    if(current_chunk->array.size() == 0 && iterated->length != 0) ////do not delete last
    {
        current_chunk->prev->next = current_chunk->next;
        current_chunk->next->prev = current_chunk->prev;

        Chunk* temp = current_chunk;
        current_chunk = current_chunk->next;
        delete temp;

        current_index = 0;
    }

    --iterated->length;
}

template<typename T>
void List<T>::Iterator::next()
{
    if(hasNext())
    {
        if(current_index < current_chunk->array.size() - 1)
        {
            ++current_index;
        }
        else
        {
            current_chunk = current_chunk->next;
            current_index = 0;
        }
    }
    else
    {
        throw Exception("iterator points on last element");
    }
}

template<typename T>
void List<T>::Iterator::prev()
{
    if(hasPrev())
    {
        if(current_index > 0)
        {
            --current_index;
        }
        else
        {
            current_chunk = current_chunk->prev;
            current_index = current_chunk->array.size() - 1;
        }
    }
    else
    {
        throw Exception("iterator points on first element");
    }
}

template<typename T>
bool List<T>::Iterator::hasNext() const
{
    return current_index < current_chunk->array.size() - 1 ||
        current_chunk->next != nullptr;
}

template<typename T>
bool List<T>::Iterator::hasPrev() const
{
    return current_index > 0 ||
        current_chunk->prev != nullptr;
}



#endif //TESTING_TEST_LIST_H
