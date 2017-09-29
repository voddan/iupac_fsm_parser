//
// Created by Daniil_Vodopian on 9/26/2017.
//

#include "SyntaxTree.h"


using std::move;

SyntaxTree::SyntaxTree(SyntaxTreeNode root) : root(move(root)) {}

SyntaxTree::SyntaxTree(SyntaxTree && other) noexcept : root((SyntaxTreeNode &&) other.root) {}
