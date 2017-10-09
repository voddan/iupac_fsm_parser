//
// Created by Daniil_Vodopian on 9/27/2017.
//

#ifndef IUPAC_FSM_PARSER_REGEXSYNTAXTREENODE_H
#define IUPAC_FSM_PARSER_REGEXSYNTAXTREENODE_H


#include <set>
#include "SyntaxTreeNode.h"

using std::set;
using std::move;

class RegexSyntaxTreeNode : public SyntaxTreeNode {
public:
    RegexSyntaxTreeNode(string nodeClass, TextPosition position);
    RegexSyntaxTreeNode(RegexSyntaxTreeNode && other) noexcept;

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

/**
 * Parses a part of a template, ignoring all special characters
 * @param position - non-empty text position
 * @returns - syntax node with children
 * */
RegexSyntaxTreeNode fromTrivialString(TextPosition position);

/**
 * "Not a Node"
 * Corresponds to an empty string
 * */
class NaN : public RegexSyntaxTreeNode {
public:
    explicit NaN(string::size_type begin) :
            RegexSyntaxTreeNode("NAN", TextPosition("", begin)) {}
};

class Concatenation : public RegexSyntaxTreeNode {
public:
    explicit Concatenation(RegexSyntaxTreeNode first,
                           RegexSyntaxTreeNode second) :
            RegexSyntaxTreeNode("CAT",
                                TextPosition(first.position.text + second.position.text,
                                             first.position.begin)) {
        addChild(move(first));
        addChild(move(second));
    }
};

class Character : public RegexSyntaxTreeNode {
public:
    explicit Character(char ch, string::size_type begin) :
            RegexSyntaxTreeNode("CH", TextPosition(string(1, ch), begin)) {}
};

class END : public RegexSyntaxTreeNode {
public:
    explicit END(string::size_type begin) :
            RegexSyntaxTreeNode("END", TextPosition("", begin)) {}
};

class Group: public RegexSyntaxTreeNode {
public:
    Group(string name, RegexSyntaxTreeNode node) :
            RegexSyntaxTreeNode(name,
                                TextPosition("(" + node.position.text + ")", node.position.begin - 1)) {
        addChild(move(node));
    }

    Group(RegexSyntaxTreeNode node) :
            RegexSyntaxTreeNode("GROUP",
                                TextPosition("(" + node.position.text + ")", node.position.begin - 1)) {
        addChild(move(node));
    }
};

class Iteration : public RegexSyntaxTreeNode {
public:
    explicit Iteration(RegexSyntaxTreeNode node) :
            RegexSyntaxTreeNode("ITER", TextPosition(node.position.text + "*",
                                                  node.position.begin)) {
        addChild(move(node));
    }
};

class PlusIteration : public RegexSyntaxTreeNode {
public:
    explicit PlusIteration(RegexSyntaxTreeNode node) :
            RegexSyntaxTreeNode("PITER", TextPosition(node.position.text + "+",
                                                  node.position.begin)) {
        addChild(move(node));
    }
};

class Option : public RegexSyntaxTreeNode {
public:
    explicit Option(RegexSyntaxTreeNode node) :
            RegexSyntaxTreeNode("OPTION", TextPosition(node.position.text + "?",
                                                  node.position.begin)) {
        addChild(move(node));
    }
};

class Combination : public RegexSyntaxTreeNode {
public:
    explicit Combination(RegexSyntaxTreeNode first,
                         RegexSyntaxTreeNode second) :
            RegexSyntaxTreeNode("COMB",
                                TextPosition(first.position.text + "|" + second.position.text,
                                             first.position.begin)) {
        addChild(move(first));
        addChild(move(second));
    }
};


#endif //IUPAC_FSM_PARSER_REGEXSYNTAXTREENODE_H
