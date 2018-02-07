//
// Created by Daniil_Vodopian on 10/3/2017.
//

#include <gtest/gtest.h>
#include <iostream>
#include <regular-fsm/RegexSyntaxTree.h>

using std::move;

TEST(TextPosition, check_equality) {
    string str("123456789");
    TextPosition p1(str, 0);
    TextPosition p2(str, 0);
    TextPosition p3(str, 1);

    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

TEST(TextPosition, check_emptiness) {
    string str("123456789");
    TextPosition p1(str, 0);
    TextPosition p2(str, 10);
    TextPosition p3("", 0);
    TextPosition p4("", 10);

    EXPECT_TRUE(!p1.empty());
    EXPECT_TRUE(!p2.empty());
    EXPECT_TRUE(p3.empty());
    EXPECT_TRUE(p4.empty());
}