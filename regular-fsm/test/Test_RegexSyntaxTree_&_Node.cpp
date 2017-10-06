//
// Created by Daniil_Vodopian on 10/3/2017.
//

#include <catch.hpp>
#include <iostream>
#include <regular-fsm/RegexSyntaxTree.h>

using std::move;

TEST_CASE("Creation & pretty printing") {
    // (ab|c?d+)*e
    // 01234567890

    Character n1('a', 1);
    Character n2('b', 2);
    Character n3('c', 4);
    Character n4('d', 6);
    Character n5('e', 10);

    Concatenation q1(move(n1), move(n2));  // ab
    Option q2(move(n3));                   // c?
    PlusIteration q3(move(n4));            // d+
    Concatenation q4(move(q2), move(q3));  // c?d+
    Combination q5(move(q1), move(q4));    // ab|c?d+
    Group q6(move(q5));                    // (ab|c?d+)
    Iteration q7(move(q6));                // (ab|c?d+)*
    Concatenation q8(move(q7), move(n5));  // (ab|c?d+)*e

    SyntaxTree tree(move(q8));


    const char * treeStr =
            "<.: (ab|c?d+)*e>\n"
            "\t<*: (ab|c?d+)*>\n"
            "\t\t<group: (ab|c?d+)>\n"
            "\t\t\t<|: ab|c?d+>\n"
            "\t\t\t\t<.: ab>\n"
            "\t\t\t\t\t<char: a>\n"
            "\t\t\t\t\t<char: b>\n"
            "\t\t\t\t</.>\n"
            "\t\t\t\t<.: c?d+>\n"
            "\t\t\t\t\t<?: c?>\n"
            "\t\t\t\t\t\t<char: c>\n"
            "\t\t\t\t\t</?>\n"
            "\t\t\t\t\t<+: d+>\n"
            "\t\t\t\t\t\t<char: d>\n"
            "\t\t\t\t\t</+>\n"
            "\t\t\t\t</.>\n"
            "\t\t\t</|>\n"
            "\t\t</group>\n"
            "\t</*>\n"
            "\t<char: e>\n"
            "</.>\n";

    CHECK(tree.prettyPrint() == treeStr);
}

TEST_CASE("A tree with auxiliary nodes") {
    // |a#
    // 012

    NaN n1(0);
    Character n2('a', 1);
    EORE n3(2);

    Combination q1(move(n1), move(n2));
    Concatenation q2(move(q1), move(n3));

    RegexSyntaxTree tree(move(q2));

    const char * treeStr =
            "<.: |a>\n"
            "\t<|: |a>\n"
            "\t\t<NaN: >\n"
            "\t\t<char: a>\n"
            "\t</|>\n"
            "\t<#: >\n"
            "</.>\n";

    CHECK(tree.prettyPrint() == treeStr);
}

TEST_CASE("Creation from a trivial string") {
    // (ab|c?d+)*e
    // 01234567890

    string str("(ab|c?d+)*e");
    RegexSyntaxTreeNode generated = fromTrivialString(TextPosition(str, 0));

    const char * treeStr =
            "<.: (ab|c?d+)*e>\n"
                    "\t<.: (ab|c?d+)*>\n"
                    "\t\t<.: (ab|c?d+)>\n"
                    "\t\t\t<.: (ab|c?d+>\n"
                    "\t\t\t\t<.: (ab|c?d>\n"
                    "\t\t\t\t\t<.: (ab|c?>\n"
                    "\t\t\t\t\t\t<.: (ab|c>\n"
                    "\t\t\t\t\t\t\t<.: (ab|>\n"
                    "\t\t\t\t\t\t\t\t<.: (ab>\n"
                    "\t\t\t\t\t\t\t\t\t<.: (a>\n"
                    "\t\t\t\t\t\t\t\t\t\t<char: (>\n"
                    "\t\t\t\t\t\t\t\t\t\t<char: a>\n"
                    "\t\t\t\t\t\t\t\t\t</.>\n"
                    "\t\t\t\t\t\t\t\t\t<char: b>\n"
                    "\t\t\t\t\t\t\t\t</.>\n"
                    "\t\t\t\t\t\t\t\t<char: |>\n"
                    "\t\t\t\t\t\t\t</.>\n"
                    "\t\t\t\t\t\t\t<char: c>\n"
                    "\t\t\t\t\t\t</.>\n"
                    "\t\t\t\t\t\t<char: ?>\n"
                    "\t\t\t\t\t</.>\n"
                    "\t\t\t\t\t<char: d>\n"
                    "\t\t\t\t</.>\n"
                    "\t\t\t\t<char: +>\n"
                    "\t\t\t</.>\n"
                    "\t\t\t<char: )>\n"
                    "\t\t</.>\n"
                    "\t\t<char: *>\n"
                    "\t</.>\n"
                    "\t<char: e>\n"
                    "</.>\n";

    CHECK(generated.prettyPrint() == treeStr);
}

TEST_CASE("Creation from an empty string") {
    string str("");
    RegexSyntaxTreeNode generated = fromTrivialString(TextPosition(str, 0));

    const char * treeStr = "<NaN: >\n";
    CHECK(generated.prettyPrint() == treeStr);
}