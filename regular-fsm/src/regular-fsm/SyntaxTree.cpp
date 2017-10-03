//
// Created by Daniil_Vodopian on 9/26/2017.
//

#include "SyntaxTree.h"


using std::move;

SyntaxTree::SyntaxTree(const SyntaxTreeNode & root) : root((SyntaxTreeNode &&) root) {}

SyntaxTree::SyntaxTree(SyntaxTree && other) noexcept : root((SyntaxTreeNode &&) other.root) {}

string SyntaxTree::prettyPrint() const {
    return root.prettyPrint();
}
