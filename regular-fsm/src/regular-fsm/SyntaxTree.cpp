//
// Created by Daniil_Vodopian on 9/26/2017.
//

#include "SyntaxTree.h"


using std::move;

SyntaxTree::SyntaxTree(unique_ptr<SyntaxTreeNode> root) : root(move(root)) {}

SyntaxTree::SyntaxTree(SyntaxTree && other) noexcept : root((unique_ptr<SyntaxTreeNode> &&) other.root) {}

string SyntaxTree::prettyPrint() const {
    return root->prettyPrint();
}
