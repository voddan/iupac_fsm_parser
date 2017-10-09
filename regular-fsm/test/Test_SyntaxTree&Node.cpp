//
// Created by Daniil_Vodopian on 10/3/2017.
//

#include <catch.hpp>
#include <iostream>
#include <regular-fsm/SyntaxTree.h>

using std::move;

TEST_CASE("Create simple SyntaxTree, pretty print it") {
    SyntaxTreeNode n1("tree", TextPosition("root", 0));
    SyntaxTreeNode n2("leaf", TextPosition("leaf1", 4));
    SyntaxTreeNode n3("leaf", TextPosition("leaf2", 9));

    CHECK(n1.prettyPrint() == "<tree text=\"root\"/>\n");
    CHECK(n2.prettyPrint() == "<leaf text=\"leaf1\"/>\n");
    CHECK(n3.prettyPrint() == "<leaf text=\"leaf2\"/>\n");

    n1.addChild(move(n2));
    n1.addChild(move(n3));


    const char * treeStr =
            "<tree text=\"root\">\n"
            "\t<leaf text=\"leaf1\"/>\n"
            "\t<leaf text=\"leaf2\"/>\n"
            "</tree>\n";

    CHECK(n1.prettyPrint() == treeStr);

    SyntaxTree tree(move(n1));

    CHECK(tree.prettyPrint() == treeStr);
}