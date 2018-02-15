//
// Created by Daniil_Vodopian on 9/27/2017.
//

#ifndef IUPAC_FSM_PARSER_REGEXSYNTAXTREENODE_H
#define IUPAC_FSM_PARSER_REGEXSYNTAXTREENODE_H


#include <set>
#include <map>
#include <memory>
#include "SyntaxTreeNode.h"

using std::set;
using std::map;
using std::move;
using std::unique_ptr;

/**
 * Base class for regex syntax tree nodes.
 *
 * Contains attributes for building a optimal FSA `StateMachine`:
 *   + `nullable` - true if this node can generate an empty sub-expression
 *   + `firstpos` - set of all nodes which can start any sub-expression of this node
 *   + `lastpos`  - set of all nodes which can end any sub-expression of this node
 */
class RegexSyntaxTreeNode : public SyntaxTreeNode {
public:
    RegexSyntaxTreeNode(string nodeClass, TextPosition position);
    RegexSyntaxTreeNode(RegexSyntaxTreeNode && other) noexcept;

    virtual void calculateAttributes();
    virtual void calculatePositionAttributes(map<RegexSyntaxTreeNode *, set<RegexSyntaxTreeNode *>> & positions);

    inline bool getNullableAttribute() const {
        return nullableAttribute;
    }
    inline const set<RegexSyntaxTreeNode *> & getFirstposAttribute() const {
        return firstposAttribute;
    }
    inline const set<RegexSyntaxTreeNode *> & getLastposAttribute() const {
        return lastposAttribute;
    }

protected:
    bool nullableAttribute;
    set<RegexSyntaxTreeNode *> firstposAttribute;
    set<RegexSyntaxTreeNode *> lastposAttribute;
};

/**
 * "Not a Node"
 * Corresponds to an empty string
 * */
class NaN : public RegexSyntaxTreeNode {
public:
    explicit NaN(string::size_type begin) :
            RegexSyntaxTreeNode("NAN", TextPosition("", begin)) {}

    void calculateAttributes() override;
};

class Concatenation : public RegexSyntaxTreeNode {
public:
    explicit Concatenation(unique_ptr<RegexSyntaxTreeNode> first,
                           unique_ptr<RegexSyntaxTreeNode> second) :
            first(move(first)), second(move(second)),
            RegexSyntaxTreeNode("CAT",
                                TextPosition(first->position.text + second->position.text,
                                             first->position.begin))
    {
        addChild(this->first.get());
        addChild(this->second.get());
    }

    void calculateAttributes() override;
    void calculatePositionAttributes(map<RegexSyntaxTreeNode *, set<RegexSyntaxTreeNode *>> & positions) override;

    const unique_ptr<RegexSyntaxTreeNode> first, second;
};

class Character : public RegexSyntaxTreeNode {
public:
    explicit Character(char ch, string::size_type begin) :
            RegexSyntaxTreeNode("CH", TextPosition(string(1, ch), begin)) {}

    void calculateAttributes() override;
};

class END : public RegexSyntaxTreeNode {
public:
    explicit END(string::size_type begin) :
            RegexSyntaxTreeNode("END", TextPosition("", begin)) {}

    void calculateAttributes() override;
};

class Group: public RegexSyntaxTreeNode {
public:
    Group(string name, unique_ptr<RegexSyntaxTreeNode> node) :
            node(move(node)),
            RegexSyntaxTreeNode(name,
                                TextPosition("(" + node->position.text + ")", node->position.begin - 1))
    {
        addChild(this->node.get());
    }

    Group(unique_ptr<RegexSyntaxTreeNode> node) : Group("GROUP", move(node)) {}

    void calculateAttributes() override;

    const unique_ptr<RegexSyntaxTreeNode> node;
};

class Template: public RegexSyntaxTreeNode {
public:
    Template(TextPosition namePosition) :
            RegexSyntaxTreeNode(namePosition.text,
                                TextPosition("%" + namePosition.text + "%", namePosition.begin - 1)) {}

    void calculateAttributes() override;
};

class Iteration : public RegexSyntaxTreeNode {
public:
    explicit Iteration(unique_ptr<RegexSyntaxTreeNode> node) :
            node(move(node)),
            RegexSyntaxTreeNode("ITER", TextPosition(node->position.text + "*",
                                                  node->position.begin))
    {
        addChild(this->node.get());
    }

    void calculateAttributes() override;
    void calculatePositionAttributes(map<RegexSyntaxTreeNode *, set<RegexSyntaxTreeNode *>> & positions) override;

    const unique_ptr<RegexSyntaxTreeNode> node;
};

class PlusIteration : public RegexSyntaxTreeNode {
public:
    explicit PlusIteration(unique_ptr<RegexSyntaxTreeNode> node) :
            node(move(node)),
            RegexSyntaxTreeNode("PITER", TextPosition(node->position.text + "+",
                                                  node->position.begin))
    {
        addChild(this->node.get());
    }

    void calculateAttributes() override;
    void calculatePositionAttributes(map<RegexSyntaxTreeNode *, set<RegexSyntaxTreeNode *>> & positions) override;

    const unique_ptr<RegexSyntaxTreeNode> node;
};

class Option : public RegexSyntaxTreeNode {
public:
    explicit Option(unique_ptr<RegexSyntaxTreeNode> node) :
            node(move(node)),
            RegexSyntaxTreeNode("OPTION", TextPosition(node->position.text + "?",
                                                  node->position.begin))
    {
        addChild(this->node.get());
    }

    void calculateAttributes() override;

    const unique_ptr<RegexSyntaxTreeNode> node;
};

class Combination : public RegexSyntaxTreeNode {
public:
    explicit Combination(unique_ptr<RegexSyntaxTreeNode> first,
                         unique_ptr<RegexSyntaxTreeNode> second) :
            first(move(first)), second(move(second)),
            RegexSyntaxTreeNode("COMB",
                                TextPosition(first->position.text + "|" + second->position.text,
                                             first->position.begin))
    {
        addChild(this->first.get());
        addChild(this->second.get());
    }

    void calculateAttributes() override;

    const unique_ptr<RegexSyntaxTreeNode> first, second;
};

/**
 * expr{a}      is represented as Count{a, a}
 * expr{a,}     is represented as Count{a}
 * expr{a, b}   is represented as Count{a, b}
 * */
class Count : public RegexSyntaxTreeNode {
public:
    explicit Count(unique_ptr<RegexSyntaxTreeNode> node, TextPosition countPosition, int minCount, int maxCount) :
            node(move(node)), minCount(minCount), maxCount(maxCount),
            RegexSyntaxTreeNode("COUNT", TextPosition(node->position.text + countPosition.text,
                                                      node->position.begin))
    {
        addChild(this->node.get());
    }

    explicit Count(unique_ptr<RegexSyntaxTreeNode> node, TextPosition countPosition, int minCount) :
            Count(move(node), move(countPosition), minCount, -1) {}

    inline bool unlimited() {
        return maxCount == -1;
    }

    void calculateAttributes() override;
    void calculatePositionAttributes(map<RegexSyntaxTreeNode *, set<RegexSyntaxTreeNode *>> & positions) override;

    const unique_ptr<RegexSyntaxTreeNode> node;
    const int minCount;
    const int maxCount;
};

#endif //IUPAC_FSM_PARSER_REGEXSYNTAXTREENODE_H
