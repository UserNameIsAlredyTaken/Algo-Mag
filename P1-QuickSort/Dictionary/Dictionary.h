//
// Created by danil on 17.10.2020.
//

#ifndef TESTING_TEST_DICTIONARY_H
#define TESTING_TEST_DICTIONARY_H

template < typename K, typename V>
class Dictionary final
{

    class Iterator{
    private:

    public:
        Iterator(){}

        const K& key() const ;
        const V& get() const ;
        void set( const V& value);
        void next();
        void prev();
        bool hasNext() const ;
        bool hasPrev() const ;

    };

public:
    Dictionary();
    ~Dictionary();
    void put( const K& key, const V& value);
    void remove( const K& key);
    bool contains( const K& key);
    const V& operator []( const K& key) const ;
    V& operator []( const K& key);
    int size() const ;

    Iterator iterator();
    const Iterator iterator() const ;
};


















#endif //TESTING_TEST_DICTIONARY_H
