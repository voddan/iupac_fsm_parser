//
// Created by Daniil_Vodopian on 9/26/2017.
//

#ifndef IUPAC_FSM_PARSER_REGEXSYNTAXTREE_H
#define IUPAC_FSM_PARSER_REGEXSYNTAXTREE_H

#include <string>
#include "StateMachine.h"

using std::string;

class RegexSyntaxTree : public SyntaxTree{
public:
    void calculateAttributes();

    void calculateNodeAttributes();

    void calculatePositionAttributes();

    string toXML();

    StateMachine buildStateMachine();
};


#endif //IUPAC_FSM_PARSER_REGEXSYNTAXTREE_H
