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
    RegexSyntaxTreeNode(const string & nodeClass, const TextPosition & position);

    void calculateAttributes();

    bool getNullableAttribute() const;
    const set<RegexSyntaxTreeNode> & getFirstposAttribute() const;
    const set<RegexSyntaxTreeNode> & getLastposAttribute() const;

private:
    bool nullableAttribute;
    set<RegexSyntaxTreeNode> firstposAttribute;
    set<RegexSyntaxTreeNode> lastposAttribute;
};


class Concatination : public RegexSyntaxTreeNode {
public:
    explicit Concatination(const TextPosition & originalPosition) :
            RegexSyntaxTreeNode(".", originalPosition) {}
};

class EORE : public RegexSyntaxTreeNode {
public:
    explicit EORE(const TextPosition & originalPosition) :
            RegexSyntaxTreeNode("#", originalPosition) {}
};

class SymbolSet : public RegexSyntaxTreeNode {
public:
    explicit SymbolSet(const TextPosition & originalPosition) :
            RegexSyntaxTreeNode("set", originalPosition) {}
};

class Group: public RegexSyntaxTreeNode {
public:
    explicit Group(const TextPosition & originalPosition) :
            RegexSyntaxTreeNode("group", originalPosition) {}
};

class Iteration : public RegexSyntaxTreeNode {
public:
    explicit Iteration(const TextPosition & originalPosition) :
            RegexSyntaxTreeNode("*", originalPosition) {}
};

class PlusIteration : public RegexSyntaxTreeNode {
public:
    explicit PlusIteration(const TextPosition & originalPosition) :
            RegexSyntaxTreeNode("+", originalPosition) {}
};

class Optional : public RegexSyntaxTreeNode {
public:
    explicit Optional(const TextPosition & originalPosition) :
            RegexSyntaxTreeNode("?", originalPosition) {}
};

class Union : public RegexSyntaxTreeNode {
public:
    explicit Union(const TextPosition & originalPosition) :
            RegexSyntaxTreeNode("|", originalPosition) {}
};


#endif //IUPAC_FSM_PARSER_REGEXSYNTAXTREENODE_H
