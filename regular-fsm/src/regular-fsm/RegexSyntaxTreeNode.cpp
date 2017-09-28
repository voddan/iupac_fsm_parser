//
// Created by Daniil_Vodopian on 9/27/2017.
//

#include "RegexSyntaxTreeNode.h"


RegexSyntaxTreeNode::RegexSyntaxTreeNode(string nodeClass, TextPosition position) :
        SyntaxTreeNode(nodeClass, position) {}

RegexSyntaxTreeNode::~RegexSyntaxTreeNode() {
    delete &firstposAttribute;
    delete &lastposAttribute;
}

bool RegexSyntaxTreeNode::getNullableAttribute() const {
    return nullableAttribute;
}

const set<RegexSyntaxTreeNode *> & RegexSyntaxTreeNode::getFirstposAttribute() const {
    return firstposAttribute;
}

const set<RegexSyntaxTreeNode *> & RegexSyntaxTreeNode::getLastposAttribute() const {
    return lastposAttribute;
}

void RegexSyntaxTreeNode::calculateAttributes() {

}
