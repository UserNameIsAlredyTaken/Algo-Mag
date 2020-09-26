//
// Created by danil on 25.09.2020.
//
#include "gtest/gtest.h"
#include "Array.h"

class ArrayFixture : public ::testing::Test {

protected:
    virtual void SetUp()
    {
        array = new Array<int>();
        arrayFloat = new Array<float>();
        arrayChar = new Array<char>();
    }

    virtual void TearDown() {
        delete array;
        delete arrayFloat;
        delete arrayChar;
    }

    Array<int>* array;
    Array<float>* arrayFloat;
    Array<char>* arrayChar;
};

//TEST_F(ArrayFixture, )
