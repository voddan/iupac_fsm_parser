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

void RegexSyntaxTreeNode::calculateAttributes() {

}
