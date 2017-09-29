//
// Created by Daniil_Vodopian on 9/26/2017.
//

#ifndef IUPAC_FSM_PARSER_REGEXSYNTAXTREE_H
#define IUPAC_FSM_PARSER_REGEXSYNTAXTREE_H

#include <string>
#include <vector>
#include <map>
#include "StateMachine.h"
#include "RegexSyntaxTreeNode.h"

using std::string;
using std::vector;
using std::map;

class RegexSyntaxTree : public SyntaxTree {
public:
    explicit RegexSyntaxTree(RegexSyntaxTreeNode root);
    RegexSyntaxTree(RegexSyntaxTree && other) noexcept;

    void calculateAttributes();

    void calculateNodeAttributes();

    void calculatePositionAttributes();

    StateMachine buildStateMachine();

private:
    map<RegexSyntaxTreeNode *, set<RegexSyntaxTreeNode *>> followposAttribute;
};




#endif //IUPAC_FSM_PARSER_REGEXSYNTAXTREE_H
