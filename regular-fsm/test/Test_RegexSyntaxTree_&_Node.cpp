//
// Created by Daniil_Vodopian on 10/3/2017.
//

#include <catch.hpp>
#include <iostream>
#include <regular-fsm/RegexSyntaxTree.h>
#include <regular-fsm/RegexParsers.h>

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
            "<CAT text=\"(ab|c?d+)*e\">\n"
            "\t<ITER text=\"(ab|c?d+)*\">\n"
            "\t\t<GROUP text=\"(ab|c?d+)\">\n"
            "\t\t\t<COMB text=\"ab|c?d+\">\n"
            "\t\t\t\t<CAT text=\"ab\">\n"
            "\t\t\t\t\t<CH text=\"a\"/>\n"
            "\t\t\t\t\t<CH text=\"b\"/>\n"
            "\t\t\t\t</CAT>\n"
            "\t\t\t\t<CAT text=\"c?d+\">\n"
            "\t\t\t\t\t<OPTION text=\"c?\">\n"
            "\t\t\t\t\t\t<CH text=\"c\"/>\n"
            "\t\t\t\t\t</OPTION>\n"
            "\t\t\t\t\t<PITER text=\"d+\">\n"
            "\t\t\t\t\t\t<CH text=\"d\"/>\n"
            "\t\t\t\t\t</PITER>\n"
            "\t\t\t\t</CAT>\n"
            "\t\t\t</COMB>\n"
            "\t\t</GROUP>\n"
            "\t</ITER>\n"
            "\t<CH text=\"e\"/>\n"
            "</CAT>\n";

    CHECK(tree.prettyPrint() == treeStr);
}

TEST_CASE("A tree with auxiliary nodes") {
    // |a#
    // 012

    NaN n1(0);
    Character n2('a', 1);
    END n3(2);

    Combination q1(move(n1), move(n2));
    Concatenation q2(move(q1), move(n3));

    RegexSyntaxTree tree(move(q2));

    const char * treeStr =
            "<CAT text=\"|a\">\n"
            "\t<COMB text=\"|a\">\n"
            "\t\t<NAN text=\"\"/>\n"
            "\t\t<CH text=\"a\"/>\n"
            "\t</COMB>\n"
            "\t<END text=\"\"/>\n"
            "</CAT>\n";

    CHECK(tree.prettyPrint() == treeStr);
}

TEST_CASE("Creation from a trivial string") {
    // (ab|c?d+)*e
    // 01234567890

    string str("(ab|c?d+)*e");
    RegexSyntaxTreeNode generated = fromTrivialString(TextPosition(str, 0));

    const char * treeStr =
            "<CAT text=\"(ab|c?d+)*e\">\n"
            "\t<CAT text=\"(ab|c?d+)*\">\n"
            "\t\t<CAT text=\"(ab|c?d+)\">\n"
            "\t\t\t<CAT text=\"(ab|c?d+\">\n"
            "\t\t\t\t<CAT text=\"(ab|c?d\">\n"
            "\t\t\t\t\t<CAT text=\"(ab|c?\">\n"
            "\t\t\t\t\t\t<CAT text=\"(ab|c\">\n"
            "\t\t\t\t\t\t\t<CAT text=\"(ab|\">\n"
            "\t\t\t\t\t\t\t\t<CAT text=\"(ab\">\n"
            "\t\t\t\t\t\t\t\t\t<CAT text=\"(a\">\n"
            "\t\t\t\t\t\t\t\t\t\t<CH text=\"(\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t<CH text=\"a\"/>\n"
            "\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t<CH text=\"b\"/>\n"
            "\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t<CH text=\"|\"/>\n"
            "\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t<CH text=\"c\"/>\n"
            "\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t<CH text=\"?\"/>\n"
            "\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t<CH text=\"d\"/>\n"
            "\t\t\t\t</CAT>\n"
            "\t\t\t\t<CH text=\"+\"/>\n"
            "\t\t\t</CAT>\n"
            "\t\t\t<CH text=\")\"/>\n"
            "\t\t</CAT>\n"
            "\t\t<CH text=\"*\"/>\n"
            "\t</CAT>\n"
            "\t<CH text=\"e\"/>\n"
            "</CAT>\n";

    CHECK(generated.prettyPrint() == treeStr);
}

TEST_CASE("Creation from an empty string") {
    string str("");
    RegexSyntaxTreeNode generated = fromTrivialString(TextPosition(str, 0));

    const char * treeStr = "<NAN text=\"\"/>\n";
    CHECK(generated.prettyPrint() == treeStr);
}