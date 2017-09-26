//
// Created by Daniil_Vodopian on 9/26/2017.
//

#include "RegexSyntaxTree.h"
#include <string>
#include <mmcobj.h>


class EOT : public RegexSyntaxTree::Node {
public:
    explicit EOT(const TextPosition & originalPosition) : Node("EOT", originalPosition) {}
};

class SymbolSet : public RegexSyntaxTree::Node {
public:
    explicit SymbolSet(const TextPosition & originalPosition) : Node("symbolset", originalPosition) {}
};

//class Group: public RegexSyntaxTree::Node {};
//class Star : public RegexSyntaxTree::Node {};
//class Plus : public RegexSyntaxTree::Node {};
//class Optional : public RegexSyntaxTree::Node {};
//class Alternative : public RegexSyntaxTree::Node {};

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
