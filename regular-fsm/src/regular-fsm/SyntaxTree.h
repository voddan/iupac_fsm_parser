//
// Created by Daniil_Vodopian on 9/26/2017.
//

#ifndef IUPAC_FSM_PARSER_SYNTAXTREE_H
#define IUPAC_FSM_PARSER_SYNTAXTREE_H

#include <string>
#include <vector>
#include <base_cpp/non_copyable.h>
#include "SyntaxTreeNode.h"

using std::string;
using std::vector;

class SyntaxTree : public indigo::NonCopyable {
public:
    explicit SyntaxTree(const SyntaxTreeNode & root);
    SyntaxTree(SyntaxTree && other) noexcept;

    string prettyPrint() const;

private:
    const SyntaxTreeNode root;
};


#endif //IUPAC_FSM_PARSER_SYNTAXTREE_H
