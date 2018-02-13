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

/**
 * A syntax tree to represent a structure of a regular expression
 */
class RegexSyntaxTree : public SyntaxTree {
public:
    explicit RegexSyntaxTree(RegexSyntaxTreeNode root);
    RegexSyntaxTree(RegexSyntaxTree && other) noexcept;

    void calculateAttributes();

    /**
     * Calculates attributes in all nodes of its tree,
     * namely `nullable`, `firstpos` and `lastpos`
     */
    void calculateNodeAttributes();

    /**
     * Calculates attributes of the syntax tree,
     * namely `followpos`
     */
    void calculatePositionAttributes();

    /**
     * @return a FSA which parses strings, represented by the structure of this tree
     */
    StateMachine buildStateMachine();

private:
    map<RegexSyntaxTreeNode *, set<RegexSyntaxTreeNode *>> followposAttribute;
};




#endif //IUPAC_FSM_PARSER_REGEXSYNTAXTREE_H
