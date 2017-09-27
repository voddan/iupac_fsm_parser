//
// Created by Daniil_Vodopian on 9/26/2017.
//

#ifndef IUPAC_FSM_PARSER_SYNTAXTREE_H
#define IUPAC_FSM_PARSER_SYNTAXTREE_H

#include <string>
#include <vector>
#include "SyntaxTreeNode.h"

using std::string;
using std::vector;

class SyntaxTree {
public:
    explicit SyntaxTree(const SyntaxTreeNode & root);

private:
    const SyntaxTreeNode root;
};


#endif //IUPAC_FSM_PARSER_SYNTAXTREE_H
