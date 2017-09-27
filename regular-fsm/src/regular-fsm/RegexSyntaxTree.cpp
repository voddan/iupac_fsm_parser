//
// Created by Daniil_Vodopian on 9/26/2017.
//

#include "RegexSyntaxTree.h"
#include "SyntaxTreeNode.h"


class EOT : public SyntaxTreeNode {
public:
    explicit EOT(const TextPosition & originalPosition) :
            SyntaxTreeNode("EOT", originalPosition) {}
};

class SymbolSet : public SyntaxTreeNode {
public:
    explicit SymbolSet(const TextPosition & originalPosition) :
            SyntaxTreeNode("symbolset", originalPosition) {}
};

//class Group: public SyntaxTreeNode {};
//class Star : public SyntaxTreeNode {};
//class Plus : public SyntaxTreeNode {};
//class Optional : public SyntaxTreeNode {};
//class Alternative : public SyntaxTreeNode {};

void RegexSyntaxTree::calculateAttributes() {

}

void RegexSyntaxTree::calculateNodeAttributes() {

}

void RegexSyntaxTree::calculatePositionAttributes() {

}

string RegexSyntaxTree::toXML() {
    return string();
}

StateMachine RegexSyntaxTree::buildStateMachine() {
    return StateMachine();
}
