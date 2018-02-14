//
// Created by Daniil_Vodopian on 9/27/2017.
//

#ifndef IUPAC_FSM_PARSER_SYNTAXTREENODE_H
#define IUPAC_FSM_PARSER_SYNTAXTREENODE_H

#include <string>
#include <vector>
#include <base_cpp/non_copyable.h>
#include "TextPosition.h"

using std::string;
using std::vector;

/**
 * A base class for syntax tree nodes.
 */
class SyntaxTreeNode : public indigo::NonCopyable {
public:
    SyntaxTreeNode(string nodeClass, TextPosition position);
    SyntaxTreeNode(SyntaxTreeNode && other) noexcept;
    virtual ~SyntaxTreeNode() = default;

    string prettyPrint(int indent = 0) const;

    void addChild(SyntaxTreeNode * child);
    void addChild(const SyntaxTreeNode * child);

    inline const vector<SyntaxTreeNode *> & getChildren() const {
        return children;
    }

    const string nodeClass;
    const TextPosition position;

private:
    vector<SyntaxTreeNode *> children;
};


#endif //IUPAC_FSM_PARSER_SYNTAXTREENODE_H
