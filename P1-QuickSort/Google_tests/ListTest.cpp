//
// Created by danil on 02.10.2020.
//

#include "gtest/gtest.h"
#include "List.h"

TEST(ListFixture, HeadInsertHeadRemoveHeadTest){
    List< int > a;
    for( int i = 0; i < 10; ++i)
    {
        a.insertHead(i);
    }


    for( int i = 9; i >= 0; --i)
    {
        EXPECT_EQ(a.head(), i);
        a.removeHead();
    }

    List< float > b;
    for( int i = 0; i < 10; ++i)
    {
        b.insertHead(i);
    }

    EXPECT_EQ(b.size(), 10);

    for( int i = 9; i >= 0; --i)
    {
        EXPECT_EQ(b.head(), i);
        b.removeHead();
    }
}

TEST(ListFixture, SizeTest){
    List< int > a;
    EXPECT_EQ(a.size(), 0);
    for( int i = 0; i < 10; ++i)
    {
        a.insertHead(i);
    }

    EXPECT_EQ(a.size(), 10);


    List< float > b;
    EXPECT_EQ(b.size(), 0);
    for( int i = 0; i < 10; ++i)
    {
        b.insertHead(i);
    }

    EXPECT_EQ(b.size(), 10);
}

TEST(ListFixture, TailInsertTailRemoveTailTest){
    List< int > a;
    for( int i = 0; i < 10; ++i)
    {
        a.insertTail(i);
    }

    for( int i = 9; i >= 0; --i)
    {
        EXPECT_EQ(a.tail(), i);
        a.removeTail();
    }

    List< float > b;
    for( int i = 0; i < 10; ++i)
    {
        b.insertTail(i);
    }

    EXPECT_EQ(b.size(), 10);

    for( int i = 9; i >= 0; --i)
    {
        EXPECT_EQ(b.tail(), i);
        b.removeTail();
    }
}

TEST(ListFixture, IteratorNextHasNextGetTest){
    List< int > a;
    for( int i = 0; i < 10; ++i)
    {
        a.insertHead(i);
    }
    int counter = 0;
    for(auto it = a.iterator(); it.hasNext(); it.next())
    {
        EXPECT_EQ(it.get(), counter++);
    }

    List< float > b;
    for( int i = 0; i < 10; ++i)
    {
        b.insertHead(i);
    }
    counter = 0;
    for(auto it = b.iterator(); it.hasNext(); it.next())
    {
        EXPECT_EQ(it.get(), counter++);
    }
}

TEST(ListFixture, IteratorPrevHasPrevGetTest){
    List< int > a;
    for( int i = 0; i < 10; ++i)
    {
        a.insertHead(i);
    }
    int counter = 0;
    auto it = a.iterator();
    for(; it.hasNext(); it.next())
    {
        EXPECT_EQ(it.get(), counter++);
    }
    EXPECT_EQ(it.get(), counter);

    for(; it.hasPrev(); it.prev())
    {
        EXPECT_EQ(it.get(), counter--);
    }
    EXPECT_EQ(it.get(), counter);

    List< float > b;
    for( int i = 0; i < 10; ++i)
    {
        b.insertHead(i);
    }
    counter = 0;
    auto itB = b.iterator();
    for(; itB.hasNext(); itB.next())
    {
        EXPECT_EQ(itB.get(), counter++);
    }
    EXPECT_EQ(itB.get(), counter);

    for(; itB.hasPrev(); itB.prev())
    {
        EXPECT_EQ(itB.get(), counter--);
    }
    EXPECT_EQ(itB.get(), counter);
}

TEST(ListFixture, IteratorSetTest){
    List< int > a;
    for( int i = 0; i < 10; ++i)
    {
        a.insertHead(0);
    }
    int counter = 0;
    auto it = a.iterator();
    for(; it.hasNext(); it.next())
    {
        it.set(counter++);
    }
    it.set(counter);

    counter = 0;
    auto itt = a.iterator();
    for(; itt.hasNext(); itt.next())
    {
        EXPECT_EQ(itt.get(), counter++);
    }
    EXPECT_EQ(itt.get(), counter);



    List< float > b;
    for( int i = 0; i < 10; ++i)
    {
        b.insertHead(0);
    }
    counter = 0;
    auto itB = b.iterator();
    for(; itB.hasNext(); itB.next())
    {
        itB.set(counter++);
    }
    itB.set(counter);

    counter = 0;
    auto ittB = b.iterator();
    for(; ittB.hasNext(); ittB.next())
    {
        EXPECT_EQ(ittB.get(), counter++);
    }
    EXPECT_EQ(ittB.get(), counter);
}

TEST(ListFixture, IteratorInsertTest){
    List< int > a;
    for( int i = 0; i < 10; ++i)
    {
        a.insertTail(0);
    }
    auto it = a.iterator();
    it.next();
    it.next();
    it.next();
    it.next();
    it.insert(999);
    a.removeTail();
    a.removeTail();
    a.removeTail();
    a.removeTail();
    EXPECT_EQ(a.tail(), 999);
}

TEST(ListFixture, IteratorRemoveTest){
    List< int > a;
    for( int i = 0; i < 10; ++i)
    {
        a.insertHead(i);
    }

    auto it = a.iterator();
    it.next();
    it.next();
    it.next();
    it.next();
    it.remove();

    EXPECT_EQ(it.get(), 5);
    EXPECT_EQ(a.size(), 9);
}