//
// Created by Daniil_Vodopian on 9/26/2017.
//

#ifndef IUPAC_FSM_PARSER_STATEMACHINE_H
#define IUPAC_FSM_PARSER_STATEMACHINE_H

#include <string>
#include "SyntaxTree.h"

using std::string;

class StateMachine {
public:
    SyntaxTree parse(string text);
};


#endif //IUPAC_FSM_PARSER_STATEMACHINE_H
