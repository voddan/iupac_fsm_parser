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


void EXPECT_NODE_ATTR(const string name, RegexSyntaxTreeNode * node, bool nullable,
                      std::initializer_list<RegexSyntaxTreeNode *> firstpos_ilist,
                      std::initializer_list<RegexSyntaxTreeNode *> lastpos_ilist)
{
    set<RegexSyntaxTreeNode *> firstpos(firstpos_ilist);
    set<RegexSyntaxTreeNode *> lastpos(lastpos_ilist);

    auto msg = "Testing node " + name;

    EXPECT_EQ(nullable, (node)->getNullableAttribute()) << msg;
    EXPECT_EQ(firstpos, (node)->getFirstposAttribute()) << msg;
    EXPECT_EQ(lastpos, (node)->getLastposAttribute()) << msg;
}

TEST(RegexSyntaxTreeNode_attributes, node_attributes) {
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


    EXPECT_NODE_ATTR("n1", n1, false, {n1}, {n1});
    EXPECT_NODE_ATTR("n2", n2, false, {n2}, {n2});
    EXPECT_NODE_ATTR("n3", n3, false, {n3}, {n3});
    EXPECT_NODE_ATTR("n4", n4, false, {n4}, {n4});
    EXPECT_NODE_ATTR("n5", n5, false, {n5}, {n5});
    EXPECT_NODE_ATTR("n6", n6, false, {n6}, {n6});

    EXPECT_NODE_ATTR("q1", q1, false, {n1, n2}, {n1, n2});
    EXPECT_NODE_ATTR("q2", q2, false, {n1, n2}, {n1, n2});
    EXPECT_NODE_ATTR("q3", q3, true,  {n1, n2}, {n1, n2});
    EXPECT_NODE_ATTR("q4", q4, false, {n1, n2, n3}, {n3});
    EXPECT_NODE_ATTR("q5", q5, false, {n1, n2, n3}, {n4});
    EXPECT_NODE_ATTR("q6", q6, false, {n1, n2, n3}, {n5});
    EXPECT_NODE_ATTR("q7", q7, false, {n1, n2, n3}, {n6});
}

TEST(RegexSyntaxTreeNode_attributes, tree_attributes) {
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

    auto treeFollowpos = tree.getFollowposAttribute();

    std::map<RegexSyntaxTreeNode *, set<RegexSyntaxTreeNode *>> treeFollowposReference;
    treeFollowposReference[n1] = set<RegexSyntaxTreeNode *>({n1, n2, n3});
    treeFollowposReference[n2] = set<RegexSyntaxTreeNode *>({n1, n2, n3});
    treeFollowposReference[n3] = set<RegexSyntaxTreeNode *>({n4});
    treeFollowposReference[n4] = set<RegexSyntaxTreeNode *>({n5});
    treeFollowposReference[n5] = set<RegexSyntaxTreeNode *>({n6});
    treeFollowposReference[n6] = set<RegexSyntaxTreeNode *>({});

    EXPECT_EQ(treeFollowpos[n1], treeFollowposReference[n1]);
    EXPECT_EQ(treeFollowpos[n2], treeFollowposReference[n2]);
    EXPECT_EQ(treeFollowpos[n3], treeFollowposReference[n3]);
    EXPECT_EQ(treeFollowpos[n4], treeFollowposReference[n4]);
    EXPECT_EQ(treeFollowpos[n5], treeFollowposReference[n5]);
    EXPECT_EQ(treeFollowpos[n6], treeFollowposReference[n6]);

    EXPECT_EQ(treeFollowposReference, treeFollowpos);
}