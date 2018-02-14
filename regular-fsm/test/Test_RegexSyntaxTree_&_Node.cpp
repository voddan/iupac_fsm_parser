//
// Created by Daniil_Vodopian on 10/3/2017.
//

#include <gtest/gtest.h>
#include <memory>
#include <regular-fsm/RegexSyntaxTree.h>
#include <regular-fsm/RegexParsers.h>

using std::move;
using std::make_unique;
using std::unique_ptr;

TEST(RegexSyntaxTree_and_Node, creation_and_pretty_printing) {
    // (ab|c?d+)*e
    // 01234567890

    auto n1 = make_unique<Character>('a', 1);
    auto n2 = make_unique<Character>('b', 2);
    auto n3 = make_unique<Character>('c', 4);
    auto n4 = make_unique<Character>('d', 6);
    auto n5 = make_unique<Character>('e', 10);

    auto q1 = make_unique<Concatenation>(move(n1), move(n2));  // ab
    auto q2 = make_unique<Option>(move(n3));                   // c?
    auto q3 = make_unique<PlusIteration>(move(n4));            // d+
    auto q4 = make_unique<Concatenation>(move(q2), move(q3));  // c?d+
    auto q5 = make_unique<Combination>(move(q1), move(q4));    // ab|c?d+
    auto q6 = make_unique<Group>(move(q5));                    // (ab|c?d+)
    auto q7 = make_unique<Iteration>(move(q6));                // (ab|c?d+)*
    auto q8 = make_unique<Concatenation>(move(q7), move(n5));  // (ab|c?d+)*e

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

    EXPECT_EQ(treeStr, tree.prettyPrint());
}

TEST(RegexSyntaxTree_and_Node, a_tree_with_auxiliary_nodes) {
    // |a#
    // 012

    auto n1 = make_unique<NaN>(0);
    auto n2 = make_unique<Character>('a', 1);
    auto n3 = make_unique<END>(2);

    auto q1 = make_unique<Combination> (move(n1), move(n2));
    auto q2 = make_unique<Concatenation> (move(q1), move(n3));

    RegexSyntaxTree tree(move(q2));

    const char * treeStr =
            "<CAT text=\"|a\">\n"
            "\t<COMB text=\"|a\">\n"
            "\t\t<NAN text=\"\"/>\n"
            "\t\t<CH text=\"a\"/>\n"
            "\t</COMB>\n"
            "\t<END text=\"\"/>\n"
            "</CAT>\n";

    EXPECT_EQ(treeStr, tree.prettyPrint());
}

TEST(RegexSyntaxTree_and_Node, creation_from_a_trivial_string) {
    // (ab|c?d+)*e
    // 01234567890

    string str("(ab|c?d+)*e");
    auto generated = parse_trivial_string(TextPosition(str, 0));

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

    EXPECT_EQ(treeStr, generated->prettyPrint());
}

TEST(RegexSyntaxTree_and_Node, creation_from_an_empty_string) {
    string str("");
    auto generated = parse_trivial_string(TextPosition(str, 0));

    const char * treeStr = "<NAN text=\"\"/>\n";
    EXPECT_EQ(treeStr, generated->prettyPrint());
}

TEST(RegexSyntaxTree_and_Node, calculating_attributes) {
    // (a|b)*abb#
    // 0123456789

    auto n1 = new Character('a', 1);
    auto n2 = new Character('b', 3);
    auto n3 = new Character('a', 6);
    auto n4 = new Character('b', 7);
    auto n5 = new Character('b', 8);
    auto n6 = new END(9);

    auto q1 = new Combination(unique_ptr<Character>(n1), unique_ptr<Character>(n2));        // a|b
    auto q2 = new Group(unique_ptr<Combination>(q1));                                       // (a|b)
    auto q3 = new Iteration(unique_ptr<Group>(q2));                                         // (a|b)*
    auto q4 = new Concatenation(unique_ptr<Iteration>(q3), unique_ptr<Character>(n3));      // (a|b)*a
    auto q5 = new Concatenation(unique_ptr<Concatenation>(q4), unique_ptr<Character>(n4));  // (a|b)*ab
    auto q6 = new Concatenation(unique_ptr<Concatenation>(q5), unique_ptr<Character>(n5));  // (a|b)*abb
    auto q7 = new Concatenation(unique_ptr<Concatenation>(q6), unique_ptr<END>(n6));        // (a|b)*abb

    RegexSyntaxTree tree{unique_ptr<Concatenation>(q7)};
    tree.calculateAttributes();


#define EXPECT_NODE_ATTR(node, nullable, firstpos_arr, lastpos_arr) \
    do {                                                            \
        set<RegexSyntaxTreeNode *> firstpos {(firstpos_arr)};       \
        set<RegexSyntaxTreeNode *> lastpos  {(lastpos_arr)};        \
                                                                    \
        EXPECT_EQ((nullable), (node)->getNullableAttribute());      \
        EXPECT_EQ(firstpos,   (node)->getFirstposAttribute());      \
        EXPECT_EQ(lastpos,    (node)->getLastposAttribute());       \
    } while(false)                                                  \


    EXPECT_NODE_ATTR(n1, false, (n1), (n1));
    EXPECT_NODE_ATTR(n2, false, (n2), (n2));
    EXPECT_NODE_ATTR(n3, false, (n3), (n3));
    EXPECT_NODE_ATTR(n4, false, (n4), (n4));
    EXPECT_NODE_ATTR(n5, false, (n5), (n5));
    EXPECT_NODE_ATTR(n6, false, (n6), (n6));

    EXPECT_NODE_ATTR(q1, false, (n1, n2), (n1, n2));
    EXPECT_NODE_ATTR(q2, false, (n1, n2), (n1, n2));
    EXPECT_NODE_ATTR(q3, true,  (n1, n2), (n1, n2));
    EXPECT_NODE_ATTR(q4, false, (n1, n2, n3), (n3));
    EXPECT_NODE_ATTR(q5, false, (n1, n2, n3), (n4));
    EXPECT_NODE_ATTR(q6, false, (n1, n2, n3), (n5));
    EXPECT_NODE_ATTR(q7, false, (n1, n2, n3), (n6));
}