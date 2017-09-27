//
// Created by Daniil_Vodopian on 9/27/2017.
//

#ifndef IUPAC_FSM_PARSER_SYNTAXTREENODE_H
#define IUPAC_FSM_PARSER_SYNTAXTREENODE_H

#include <string>
#include <vector>
#include "TextPosition.h"

using std::string;
using std::vector;


class SyntaxTreeNode {
public:
    SyntaxTreeNode(const string & nodeClass, const TextPosition & position);

    string prettyPrint(int indent = 0);

    void addChild(SyntaxTreeNode & child);

public:
    const string nodeClass;
    const TextPosition position;

private:
    vector<SyntaxTreeNode> children;
};


#endif //IUPAC_FSM_PARSER_SYNTAXTREENODE_H
