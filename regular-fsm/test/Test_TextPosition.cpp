//
// Created by Daniil_Vodopian on 10/3/2017.
//

#include <catch.hpp>
#include <iostream>
#include <regular-fsm/RegexSyntaxTree.h>

using std::move;

TEST_CASE("Initialisation") {
    string str("123456789");
    TextPosition p1(str);
    TextPosition p2(str, 0);
    TextPosition p3(str, 0, str.length());

    CHECK(p1 == p2);
    CHECK(p2 == p3);
}

TEST_CASE("Emptiness") {
    string str("123456789");
    TextPosition p1(str, 0);
    TextPosition p2(str, 10);
    TextPosition p3("", 0);
    TextPosition p4("", 10);

    CHECK(!p1.empty());
    CHECK(!p2.empty());
    CHECK(p3.empty());
    CHECK(p4.empty());
}