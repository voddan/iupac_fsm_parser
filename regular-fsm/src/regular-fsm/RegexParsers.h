//
// Created by Daniil_Vodopian on 10/10/2017.
//

#ifndef IUPAC_FSM_PARSER_REGEXPARSERS_H
#define IUPAC_FSM_PARSER_REGEXPARSERS_H

#include <vector>
#include <memory>
#include "TextPosition.h"
#include "RegexSyntaxTreeNode.h"

using std::vector;

/**
 * REGEX grammar used:
 *
 * extended_reg_exp   -> ERE_branch .
 * extended_reg_exp   -> extended_reg_exp `|` ERE_branch .
 *
 * ERE_branch         -> ERE_expression .
 * ERE_branch         -> ERE_branch ERE_expression .
 *
 * ERE_expression     -> ORD_CHAR .
 * ERE_expression     -> `(` extended_reg_exp `)` .
 * ERE_expression     -> `%` TEMPLATE_NAME `%` .
 * ERE_expression     -> ORD_CHAR ERE_dupl_symbol.
 * ERE_expression     -> `(` extended_reg_exp `)` ERE_dupl_symbol.
 * ERE_expression     -> `%` TEMPLATE_NAME `%` ERE_dupl_symbol.
 *
 * ERE_dupl_symbol    -> `*` .
 * ERE_dupl_symbol    -> `+` .
 * ERE_dupl_symbol    -> `?` .
 * ERE_dupl_symbol    -> `{` DUP_COUNT               `}` .
 * ERE_dupl_symbol    -> `{` DUP_COUNT `,`           `}` .
 * ERE_dupl_symbol    -> `{` DUP_COUNT `,` DUP_COUNT `}` .
 * */

vector<TextPosition> split(char delimiter, TextPosition position);

unique_ptr<RegexSyntaxTreeNode> parse_extended_reg_exp(TextPosition position);

unique_ptr<RegexSyntaxTreeNode> parse_ERE_branch(TextPosition position);

unique_ptr<RegexSyntaxTreeNode> parse_ERE_dupl_symbol(TextPosition position, unique_ptr<RegexSyntaxTreeNode> previous);

/**
 * Parses a part of a template, ignoring all special characters
 * @param position - non-empty text position
 * @returns - syntax node with children
 * */
unique_ptr<RegexSyntaxTreeNode> parse_trivial_string(TextPosition position);

template <typename JOINT>
void hang_up_to_the_root(unique_ptr<RegexSyntaxTreeNode> & root, unique_ptr<RegexSyntaxTreeNode> node) {
    if(root)
        root.reset(new JOINT(move(root), move(node)));
    else
        root = move(node);
}


#endif //IUPAC_FSM_PARSER_REGEXPARSERS_H
