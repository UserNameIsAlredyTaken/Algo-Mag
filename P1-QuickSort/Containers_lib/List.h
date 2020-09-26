//
// Created by danil on 26.09.2020.
//

#ifndef TESTING_TEST_LIST_H
#define TESTING_TEST_LIST_H


template < typename T>
class List final {

private:

    class Chunk{
    private:
        Chunk(){
            next = nullptr;
            prev = nullptr;
        }
        Chunk(const T& value){
            this->value = value;
            next = nullptr;
            prev = nullptr;
        }

    public:
        T value;
        Chunk next;
        Chunk prev;
    };

    class Iterator{
    private:
        List<T>& iterated;
        Chunk& current_chunk;

    public:
        Iterator(List<T>& iterated) : iterated(iterated), current_chunk(iterated.tail_chunk){}

        const T& get() const ;
        void set( const T& value);
        void insert( const T& value);
        void remove();
        void next();
        void prev();
        bool hasNext() const ;
        bool hasPrev() const ;
    };

    Chunk& head_chunk;
    Chunk& tail_chunk;

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
List<T>::List()
{
    Chunk& chunk = new Chunk();
    head_chunk = chunk;
    tail_chunk = chunk;
    length = 0;
}

template<typename T>
List<T>::~List(){
    while(head_chunk.prev){
        removeHead();
    }
    delete head_chunk;
    head_chunk = nullptr;
    tail_chunk = nullptr;
}


template<typename T>
void List<T>::insertHead( const T& value)
{
    Chunk& chunk = new Chunk(value);
    if(length == 0)
    {
        head_chunk.value = value;
        length = 1;
    }
    else
    {
        chunk.prev = head_chunk;
        head_chunk.next = chunk;
        head_chunk = chunk;
        ++length;
    }
}

template<typename T>
void List<T>::insertTail(const T &value)
{
    Chunk& chunk = new Chunk(value);
    if(length == 0){
        tail_chunk.value = value;
        length = 1;
    }else{
        chunk.next = tail_chunk;
        tail_chunk.prev = chunk;
        tail_chunk = chunk;
        ++length;
    }
}

template<typename T>
void List<T>::removeHead()
{
    if(!head_chunk.prev) return; ////do not delete last

    head_chunk = head_chunk.prev;
    delete head_chunk.next;
    head_chunk.next = nullptr;
    --length;
}

template<typename T>
void List<T>::removeTail()
{
    if(!tail_chunk.next) return; ////do not delete last

    tail_chunk = tail_chunk.next;
    delete tail_chunk.prev;
    tail_chunk.prev = nullptr;
    --length;
}

template<typename T>
const T& List<T>::head() const
{
    return head_chunk.value;
}

template<typename T>
const T& List<T>::tail() const
{
    return tail_chunk.value;
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
    return current_chunk.value;
}

template<typename T>
void List<T>::Iterator::set( const T& value){
    current_chunk.value = value;
}

template<typename T>
void List<T>::Iterator::insert( const T& value)
{
    if(iterated.length == 0)
    {
        current_chunk.value = value;
        iterated.length = 1;
    }
    else
    {
        Chunk& chunk = new Chunk(value);
        chunk.prev = current_chunk.prev;
        chunk.next = current_chunk;
        current_chunk.prev.next = chunk;
        current_chunk.prev = chunk;
        ++iterated.length;
    }
}

template<typename T>
void List<T>::Iterator::remove()
{
    if(iterated.length == 0) return;

    current_chunk.prev.next = current_chunk.next;
    current_chunk.next.prev = current_chunk.prev;

    Chunk& temp = current_chunk;
    current_chunk = current_chunk.next;
    delete current_chunk;
    --iterated.length;
}

template<typename T>
void List<T>::Iterator::next()
{
    if(hasNext())
    {
        throw "iterator points on last element";
    }
    else
    {
        current_chunk = current_chunk.next;
    }
}

template<typename T>
void List<T>::Iterator::prev()
{
    if(hasPrev())
    {
        throw "iterator points on first element";
    }
    else
    {
        current_chunk = current_chunk.prev;
    }
}

template<typename T>
bool List<T>::Iterator::hasNext() const
{
    return current_chunk.next == nullptr;
}

template<typename T>
bool List<T>::Iterator::hasPrev() const
{
    return current_chunk.prev == nullptr;
}



#endif //TESTING_TEST_LIST_H
