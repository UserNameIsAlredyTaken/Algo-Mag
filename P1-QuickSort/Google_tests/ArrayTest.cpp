//
// Created by danil on 25.09.2020.
//
#include "gtest/gtest.h"
#include "Array.h"


TEST(ArrayFixture, InsertGetTest){
    Array< int > a;
    for ( int i = 0; i < 10; ++i)
        a.insert(i);

    bool intBeforeThresholdTestPassed = true;
    for( int i = 0; i < 10; ++i)
    {
        if(a[i] != i)
        {
            intBeforeThresholdTestPassed = false;
            break;
        }
    }

    Array< float > b;
    for ( int i = 0; i < 10; ++i)
        b.insert((float)i);

    bool floatBeforeThresholdTestPassed = true;
    for( int i = 0; i < 10; ++i)
    {
        if(b[i] != i)
        {
            intBeforeThresholdTestPassed = false;
            break;
        }
    }

    EXPECT_EQ(intBeforeThresholdTestPassed, true);
    EXPECT_EQ(floatBeforeThresholdTestPassed, true);
}

TEST(ArrayFixture, InsertWiderTest){
    Array< int > a;
    for ( int i = 0; i < 20; ++i)
        a.insert(i);

    bool intAfterThresholdTestPassed = true;
    for( int i = 0; i < 20; ++i)
    {
        if(a[i] != i)
        {
            intAfterThresholdTestPassed = false;
            break;
        }
    }

    Array< float > b;
    for ( int i = 0; i < 20; ++i)
        b.insert((float )i);

    bool floatAfterThresholdTestPassed = true;
    for( int i = 0; i < 20; ++i)
    {
        if(b[i] != i)
        {
            intAfterThresholdTestPassed = false;
            break;
        }
    }

    EXPECT_EQ(intAfterThresholdTestPassed, true);
    EXPECT_EQ(floatAfterThresholdTestPassed, true);
}

TEST(ArrayFixture, InsertIndesxTest){
    Array< int > a;
    for ( int i = 0; i < 20; ++i)
        a.insert(i);

    a.insert(11, 999);

    Array< float > b;
    for ( int i = 0; i < 20; ++i)
        b.insert((float )i);

    b.insert(11, 999.0f);

    EXPECT_EQ(a[11], 999);
    EXPECT_EQ(a[12], 11);
    EXPECT_EQ(b[11], 999.0f);
    EXPECT_EQ(b[12], 11.0f);
}

TEST(ArrayFixture, RemoveTest){
    Array< int > a;
    for ( int i = 0; i < 20; ++i)
        a.insert(i);

    a.remove(11);

    Array< float > b;
    for ( int i = 0; i < 20; ++i)
        b.insert((float )i);

    b.remove(11);

    EXPECT_EQ(a[11], 12);
    EXPECT_EQ(b[11], 12.0f);
}

TEST(ArrayFixture, SetTest){
    Array< int > a;
    for ( int i = 0; i < 20; ++i)
        a.insert(i);

    a[11] = 999;

    Array< float > b;
    for ( int i = 0; i < 20; ++i)
        b.insert((float )i);

    b[11] = 999.0f;

    EXPECT_EQ(a[11], 999);
    EXPECT_EQ(b[11], 999.0f);
}

TEST(ArrayFixture, SizeTest){
    Array< int > a;
    for ( int i = 0; i < 34; ++i)
        a.insert(i);

    Array< float > b;
    for ( int i = 0; i < 43; ++i)
        b.insert((float)i);


    EXPECT_EQ(a.size(), 34);
    EXPECT_EQ(b.size(), 43);
}

TEST(ArrayFixture, ItearatorNextHasNextTest){
    Array< int > a;
    for ( int i = 0; i < 34; ++i)
        a.insert(i);

    int intCounter = 0;
    for(auto it = a.iterator(); it.hasNext(); it.next()){
        ++intCounter;
    }
    ++intCounter;


    Array< float > b;
    for ( int i = 0; i < 43; ++i)
        b.insert((float)i);

    int floatCounter = 0;
    for(auto it = b.iterator(); it.hasNext(); it.next()){
        ++floatCounter;
    }
    ++floatCounter;


    EXPECT_EQ(intCounter, 34);
    EXPECT_EQ(floatCounter, 43);
}

TEST(ArrayFixture, ItearatorSetTest){
    Array< int > a;
    for ( int i = 0; i < 6; ++i)
        a.insert(0);

    int counter = 0;
    auto it = a.iterator();
    for (; it.hasNext(); it.next())
        it.set(counter++);
    it.set(counter);

    bool intTest = true;
    for ( int i = 0; i < 6; ++i)
    {
        if(a[i] != i)
        {
            intTest = false;
            break;
        }
    }

    Array< int > b;
    for ( int i = 0; i < 6; ++i)
        b.insert(0);

    counter = 0;
    auto itB = b.iterator();
    for ( ; itB.hasNext(); itB.next())
        itB.set(counter++);
    itB.set(counter++);

    bool floatTest = true;
    for ( int i = 0; i < 6; ++i)
    {
        if(b[i] != i)
        {
            floatTest = false;
            break;
        }
    }

    EXPECT_EQ(intTest, true);
    EXPECT_EQ(floatTest, true);
}

TEST(ArrayFixture, ItearatorGetTest){
    Array< int > a;
    for ( int i = 0; i < 6; ++i)
        a.insert(i);

    int counter = 0;
    bool intTest = true;
    for ( auto it = a.iterator(); it.hasNext(); it.next())
    {
        if(it.get() != counter++)
        {
            intTest = false;
            break;
        }
    }

    Array< int > b;
    for ( int i = 0; i < 6; ++i)
        a.insert(i);

    counter = 0;
    bool floatTest = true;
    for ( auto it = b.iterator(); it.hasNext(); it.next())
    {
        if(it.get() != counter++)
        {
            intTest = false;
            break;
        }
    }

    EXPECT_EQ(intTest, true);
    EXPECT_EQ(floatTest, true);
}

TEST(ArrayFixture, ItearatorInsertTest){
    Array< int > a;
    for ( int i = 0; i < 20; ++i)
        a.insert(i);

    auto itA = a.iterator();
    for (int i = 0; i < 11; itA.next(), ++i){}
    itA.insert(999);

    Array< int > b;
    for ( int i = 0; i < 20; ++i)
        b.insert((float)i);

    auto itB = b.iterator();
    for (int i = 0; i < 11; itB.next(), ++i){}
    itB.insert(999.0f);



    EXPECT_EQ(a[11], 999);
    EXPECT_EQ(itA.get(), 999);
    EXPECT_EQ(a[12], 11);

    EXPECT_EQ(b[11], 999.0f);
    EXPECT_EQ(itB.get(), 999.0f);
    EXPECT_EQ(b[12], 11.0f);
}

TEST(ArrayFixture, ItearatorRemoveTest){
    Array< int > a;
    for ( int i = 0; i < 20; ++i)
        a.insert(i);

    auto itA = a.iterator();
    for (int i = 0; i < 11; itA.next(), ++i){}
    itA.remove();

    Array< int > b;
    for ( int i = 0; i < 20; ++i)
        b.insert((float)i);

    auto itB = b.iterator();
    for (int i = 0; i < 11; itB.next(), ++i){}
    itB.remove();

    EXPECT_EQ(a[11], 12);
    EXPECT_EQ(itA.get(), 12);
    EXPECT_EQ(a.size(), 19);

    EXPECT_EQ(b[11], 12.0f);
    EXPECT_EQ(itB.get(), 12.0f);
    EXPECT_EQ(b.size(), 19);
}

TEST(ArrayFixture, ItearatorPrevHasPrevTest){
    Array< int > a;
    for ( int i = 0; i < 20; ++i)
        a.insert(i);

    auto itA = a.iterator();
    for (; itA.hasNext(); itA.next()){}

    bool intTest = true;
    for(int i = 19; itA.hasPrev(); --i, itA.prev())
    {
        if(itA.get() != a[i]){
            intTest = false;
            break;
        }
    }

    Array< int > b;
    for ( int i = 0; i < 20; ++i)
        b.insert(i);

    auto itB = b.iterator();
    for (; itB.hasNext(); itB.next()){}

    bool floatTest = true;
    for(int i = 19; itB.hasPrev(); --i, itB.prev())
    {
        if(itB.get() != b[i]){
            floatTest = false;
            break;
        }
    }

    EXPECT_EQ(intTest, true);
    EXPECT_EQ(floatTest, true);
}

TEST(ArrayFixture, ItearatorToIndexTest){
    Array< int > a;
    for ( int i = 0; i < 20; ++i)
        a.insert(i);

    auto itA = a.iterator();
    itA.toIndex(11);

    Array< int > b;
    for ( int i = 0; i < 20; ++i)
        b.insert(i);

    auto itB = b.iterator();
    itB.toIndex(11);

    EXPECT_EQ(itA.get(), 11);
    EXPECT_EQ(itB.get(), 11.0f);
}