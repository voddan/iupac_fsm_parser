//
// Created by Daniil_Vodopian on 9/26/2017.
//

#ifndef IUPAC_FSM_PARSER_REGEXSYNTAXTREE_H
#define IUPAC_FSM_PARSER_REGEXSYNTAXTREE_H

#include <string>
#include <vector>
#include "StateMachine.h"
#include "RegexSyntaxTreeNode.h"

using std::string;
using std::vector;

class RegexSyntaxTree : public SyntaxTree {
public:
    explicit RegexSyntaxTree(RegexSyntaxTreeNode & root);

    void calculateAttributes();

    void calculateNodeAttributes();

    void calculatePositionAttributes();

    StateMachine buildStateMachine();

private:
//    const RegexSyntaxTreeNode root; TODO: reuse `root` from `SyntaxTree`
    vector<RegexSyntaxTreeNode> positions;
};




#endif //IUPAC_FSM_PARSER_REGEXSYNTAXTREE_H
