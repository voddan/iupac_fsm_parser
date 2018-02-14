//
// Created by Daniil_Vodopian on 9/26/2017.
//

#ifndef IUPAC_FSM_PARSER_SYNTAXTREE_H
#define IUPAC_FSM_PARSER_SYNTAXTREE_H

#include <string>
#include <vector>
#include <memory>
#include <base_cpp/non_copyable.h>
#include "SyntaxTreeNode.h"

using std::string;
using std::vector;
using std::unique_ptr;

/**
 * An abstract class to encapsulate a tree of `SyntaxTreeNode`.
 *
 * Supposed to contain general tree-walking procedures such as `prettyPrint()`
 */
class SyntaxTree : public indigo::NonCopyable {
public:
    explicit SyntaxTree(SyntaxTreeNode & root);
    SyntaxTree(SyntaxTree && other) noexcept;
    virtual ~SyntaxTree() = default;

    string prettyPrint() const;

protected:
    const unique_ptr<SyntaxTreeNode> root;
};


#endif //IUPAC_FSM_PARSER_SYNTAXTREE_H
