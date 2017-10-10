//
// Created by Daniil_Vodopian on 10/10/2017.
//

#ifndef IUPAC_FSM_PARSER_REGEXPARSERS_H
#define IUPAC_FSM_PARSER_REGEXPARSERS_H

#include <vector>
#include "TextPosition.h"
#include "RegexSyntaxTreeNode.h"

using std::vector;

vector<TextPosition> split(char delimiter, TextPosition position);

RegexSyntaxTreeNode parse_ERE_dupl_symbol(TextPosition position, RegexSyntaxTreeNode previous);

/**
 * Parses a part of a template, ignoring all special characters
 * @param position - non-empty text position
 * @returns - syntax node with children
 * */
RegexSyntaxTreeNode fromTrivialString(TextPosition position);


#endif //IUPAC_FSM_PARSER_REGEXPARSERS_H
