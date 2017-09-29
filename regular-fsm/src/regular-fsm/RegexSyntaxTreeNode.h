//
// Created by Daniil_Vodopian on 9/27/2017.
//

#ifndef IUPAC_FSM_PARSER_REGEXSYNTAXTREENODE_H
#define IUPAC_FSM_PARSER_REGEXSYNTAXTREENODE_H


#include <set>
#include "SyntaxTreeNode.h"

using std::set;

class RegexSyntaxTreeNode : public SyntaxTreeNode {
public:
    RegexSyntaxTreeNode(string nodeClass, TextPosition position);
    RegexSyntaxTreeNode(RegexSyntaxTreeNode && other) noexcept;

//    #pragma ide diagnostic ignored "HidingNonVirtualFunction"
    inline const vector<RegexSyntaxTreeNode *> & getChildren() const {
        return (const vector<RegexSyntaxTreeNode *> &) SyntaxTreeNode::getChildren();
    }

    void calculateAttributes();

    inline bool getNullableAttribute() const {
        return nullableAttribute;
    }
    inline const set<RegexSyntaxTreeNode *> & getFirstposAttribute() const {
        return firstposAttribute;
    }
    inline const set<RegexSyntaxTreeNode *> & getLastposAttribute() const {
        return lastposAttribute;
    }

private:
    bool nullableAttribute;
    set<RegexSyntaxTreeNode *> firstposAttribute;
    set<RegexSyntaxTreeNode *> lastposAttribute;
};


class Concatination : public RegexSyntaxTreeNode {
public:
    explicit Concatination(TextPosition originalPosition) :
            RegexSyntaxTreeNode(".", originalPosition) {}
};

class EORE : public RegexSyntaxTreeNode {
public:
    explicit EORE(TextPosition originalPosition) :
            RegexSyntaxTreeNode("#", originalPosition) {}
};

class SymbolSet : public RegexSyntaxTreeNode {
public:
    explicit SymbolSet(TextPosition originalPosition) :
            RegexSyntaxTreeNode("set", originalPosition) {}
};

class Group: public RegexSyntaxTreeNode {
public:
    explicit Group(TextPosition originalPosition) :
            RegexSyntaxTreeNode("group", originalPosition) {}
};

class Iteration : public RegexSyntaxTreeNode {
public:
    explicit Iteration(TextPosition originalPosition) :
            RegexSyntaxTreeNode("*", originalPosition) {}
};

class PlusIteration : public RegexSyntaxTreeNode {
public:
    explicit PlusIteration(TextPosition originalPosition) :
            RegexSyntaxTreeNode("+", originalPosition) {}
};

class Optional : public RegexSyntaxTreeNode {
public:
    explicit Optional(TextPosition originalPosition) :
            RegexSyntaxTreeNode("?", originalPosition) {}
};

class Union : public RegexSyntaxTreeNode {
public:
    explicit Union(TextPosition originalPosition) :
            RegexSyntaxTreeNode("|", originalPosition) {}
};


#endif //IUPAC_FSM_PARSER_REGEXSYNTAXTREENODE_H
