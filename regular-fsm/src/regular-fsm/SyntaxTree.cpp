//
// Created by Daniil_Vodopian on 9/26/2017.
//

#include "SyntaxTree.h"
#include <string>
#include <sstream>

string SyntaxTree::Node::prettyPrint(int indent) {
    std::ostringstream str;
    string indent_str(indent, '\t');

    str << indent_str << "<" << nodeClass << ": " << origianalPosition.text << ">" << std::endl;

    if(!children.empty()) {
        for(auto child: children) {
            str << child.prettyPrint(indent + 1);
        }
        str << indent_str << "</" << nodeClass << ">";
    }
    return str.str();
}

void SyntaxTree::Node::addChild(Node & child) {
    children.push_back(child);
}

SyntaxTree::Node::Node(const string & nodeClass,
                       const TextPosition & origianalPosition) : nodeClass(nodeClass),
                                                                origianalPosition(origianalPosition) {}
