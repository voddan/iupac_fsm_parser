//
// Created by Daniil_Vodopian on 9/27/2017.
//

#include "SyntaxTreeNode.h"


#include <sstream>

using std::move;

SyntaxTreeNode::SyntaxTreeNode(string nodeClass, TextPosition position) :
        nodeClass(move(nodeClass)), position(move(position)) {}

SyntaxTreeNode::SyntaxTreeNode(SyntaxTreeNode && other) noexcept :
        nodeClass(other.nodeClass), position(other.position) {
    children = move(other.children);
}

string SyntaxTreeNode::prettyPrint(int indent) const {
    std::ostringstream str;
    string indent_str(indent, '\t');

    str << indent_str << "<" << nodeClass << " text=\"" << position.text << "\"";

    if(!children.empty()) {
        str << ">" << std::endl;

        for(auto& child: children) {
            str << child->prettyPrint(indent + 1);
        }
        str << indent_str << "</" << nodeClass << ">" << std::endl;
    } else {
        str << "/>" << std::endl;
    }

    return str.str();
}

void SyntaxTreeNode::addChild(SyntaxTreeNode * child) {
	children.push_back(child);
}

void SyntaxTreeNode::addChild(const SyntaxTreeNode * child) {
	addChild(const_cast<SyntaxTreeNode *>(child));
}
