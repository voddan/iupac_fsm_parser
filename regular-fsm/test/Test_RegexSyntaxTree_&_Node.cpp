//
// Created by Daniil_Vodopian on 10/3/2017.
//

#include <catch.hpp>
#include <iostream>
#include <regular-fsm/RegexSyntaxTree.h>

using std::move;

TEST_CASE("Create simple RegexSyntaxTree, pretty print it") {
    RegexSyntaxTreeNode n1("tree", TextPosition("root", 0, 3));
    RegexSyntaxTreeNode n2("leaf", TextPosition("leaf1", 4, 8));
    RegexSyntaxTreeNode n3("leaf", TextPosition("leaf2", 9, 13));

    CHECK(n1.prettyPrint() == "<tree: root>\n");
    CHECK(n2.prettyPrint() == "<leaf: leaf1>\n");
    CHECK(n3.prettyPrint() == "<leaf: leaf2>\n");

    n1.addChild(move(n2));
    n1.addChild(move(n3));


    const char * treeStr =
            "<tree: root>\n"
            "\t<leaf: leaf1>\n"
            "\t<leaf: leaf2>\n"
            "</tree>\n";

    CHECK(n1.prettyPrint() == treeStr);

    SyntaxTree tree(move(n1));

    CHECK(tree.prettyPrint() == treeStr);
}