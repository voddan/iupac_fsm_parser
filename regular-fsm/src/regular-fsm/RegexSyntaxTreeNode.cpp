//
// Created by Daniil_Vodopian on 9/27/2017.
//

#include "RegexSyntaxTreeNode.h"

#include <memory>


using std::move;

RegexSyntaxTreeNode::RegexSyntaxTreeNode(string nodeClass, TextPosition position) :
        SyntaxTreeNode(move(nodeClass), move(position)) {}

RegexSyntaxTreeNode::RegexSyntaxTreeNode(RegexSyntaxTreeNode && other) noexcept : SyntaxTreeNode(move(other)) {
    nullableAttribute = other.nullableAttribute;
    firstposAttribute = move(other.firstposAttribute);
    lastposAttribute = move(other.lastposAttribute);
}


//TODO: implement
void RegexSyntaxTreeNode::calculateAttributes() {
}
