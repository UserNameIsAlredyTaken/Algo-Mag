//
// Created by danil on 24.10.2020.
//

#include <QuickSorter.h>
#include <algorithm>
#include "gtest/gtest.h"
#include "../Dictionary/Dictionary.h"
#include "Array.h"

TEST(DictionaryFixture, PutContainsTest){
    Dictionary<std::string, int > npc;
    npc.put("health", 10);
    npc.put("armor", 20);
    npc.put("ammo", 5);

    EXPECT_EQ(npc.contains("ammo"), true);
    EXPECT_EQ(npc.contains("o"), false);
}

TEST(DictionaryFixture, RemoveTest){
    Dictionary<std::string, int > npc;
    npc.put("health", 10);
    npc.put("armor", 20);
    npc.put("ammo", 5);

    EXPECT_EQ(npc.contains("ammo"), true);
    npc.remove("ammo");
    EXPECT_EQ(npc.contains("ammo"), false);
}

TEST(DictionaryFixture, OperatorTest){
    Dictionary<std::string, int > npc;
    npc.put("health", 10);
    npc.put("armor", 20);
    npc.put("ammo", 5);

    EXPECT_EQ(npc["ammo"], 5);
    npc["ammo"] = 6;
    EXPECT_EQ(npc["ammo"], 6);
}

TEST(DictionaryFixture, SizeTest){
    Dictionary<std::string, int > npc;
    EXPECT_EQ(npc.size(), 0);

    npc.put("health", 10);
    npc.put("armor", 20);
    npc.put("ammo", 5);

    EXPECT_EQ(npc.size(), 3);
    npc.put("ao", 5);
    EXPECT_EQ(npc.size(), 4);
}

TEST(DictionaryFixture, IteratorKeyGetTest){
    Dictionary<std::string, int > npc;
    npc.put("health", 10);

    auto it = npc.iterator();

    EXPECT_EQ(it.key(), "health");
    EXPECT_EQ(it.get(), 10);
}

TEST(DictionaryFixture, IteratorSetTest){
    Dictionary<std::string, int > npc;
    npc.put("health", 10);

    auto it = npc.iterator();
    it.set(100);

    EXPECT_EQ(it.get(), 100);
}

TEST(DictionaryFixture, IteratorNextHasNExtTest){
    Dictionary<std::string, int > npc;
    npc.put("health", 10);
    npc.put("armor", 20);
    npc.put("ammo", 5);

    std::string keys[3];
    int i = 0;
    for ( auto it = npc.iterator(); it.hasNext(); it.next())
    {
        keys[i] = it.key();
        ++i;
    }

    std::sort(keys, keys + sizeof(keys)/sizeof(keys[0]));


    EXPECT_EQ(keys[0], "ammo");
    EXPECT_EQ(keys[1], "armor");
    EXPECT_EQ(keys[2], "health");
}
