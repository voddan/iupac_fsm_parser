//
// Created by Daniil_Vodopian on 10/3/2017.
//

#include <gtest/gtest.h>
#include <iostream>
#include <regular-fsm/SyntaxTree.h>

using std::move;

TEST(SyntaxTreeAndNode, create_simple_SyntaxTree_and_pretty_print_it) {
    auto n1 = std::make_unique<SyntaxTreeNode> ("tree", TextPosition("root", 0));
    auto n2 = std::make_unique<SyntaxTreeNode> ("leaf", TextPosition("leaf1", 4));
    auto n3 = std::make_unique<SyntaxTreeNode> ("leaf", TextPosition("leaf2", 9));

    EXPECT_EQ("<tree text=\"root\"/>\n", n1->prettyPrint());
    EXPECT_EQ("<leaf text=\"leaf1\"/>\n", n2->prettyPrint());
    EXPECT_EQ("<leaf text=\"leaf2\"/>\n", n3->prettyPrint());

    n1->addChild(n2.get());
    n1->addChild(n3.get());


    const char * treeStr =
            "<tree text=\"root\">\n"
            "\t<leaf text=\"leaf1\"/>\n"
            "\t<leaf text=\"leaf2\"/>\n"
            "</tree>\n";

    EXPECT_EQ(treeStr, n1->prettyPrint());

    SyntaxTree tree(move(n1));

    EXPECT_EQ(treeStr, tree.prettyPrint());
}