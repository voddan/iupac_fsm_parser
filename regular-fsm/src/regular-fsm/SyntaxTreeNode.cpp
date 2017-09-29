//
// Created by Daniil_Vodopian on 9/27/2017.
//

#include "SyntaxTreeNode.h"


#include <sstream>

using std::move;

SyntaxTreeNode::SyntaxTreeNode(string nodeClass, TextPosition position) :
        nodeClass(nodeClass), position(position) {}

SyntaxTreeNode::SyntaxTreeNode(SyntaxTreeNode && other) noexcept :
        nodeClass(other.nodeClass), position(other.position) {
    children = move(other.children);
}

string SyntaxTreeNode::prettyPrint(int indent) {
    std::ostringstream str;
    string indent_str(indent, '\t');

    str << indent_str << "<" << nodeClass << ": " << position.text << ">" << std::endl;

    if(!children.empty()) {
        for(auto child: children) {
            str << child->prettyPrint(indent + 1);
        }
        str << indent_str << "</" << nodeClass << ">";
    }
    return str.str();
}

void SyntaxTreeNode::addChild(SyntaxTreeNode child) {
	children.push_back(move(&child));
}
