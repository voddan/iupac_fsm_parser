//
// Created by Daniil_Vodopian on 9/27/2017.
//

#ifndef IUPAC_FSM_PARSER_TEXTPOSITION_H
#define IUPAC_FSM_PARSER_TEXTPOSITION_H

#include <string>

using std::string;

struct TextPosition {
    const string text;
    const int start;
    const int end;
};


#endif //IUPAC_FSM_PARSER_TEXTPOSITION_H
