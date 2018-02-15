//
// Created by Daniil_Vodopian on 9/27/2017.
//

#include "RegexSyntaxTreeNode.h"

#include <memory>


using std::move;

void setInfuse(set<RegexSyntaxTreeNode *> & dest, const set<RegexSyntaxTreeNode *> & src) {
    dest.insert(src.begin(), src.end());
}

RegexSyntaxTreeNode::RegexSyntaxTreeNode(string nodeClass, TextPosition position) :
        SyntaxTreeNode(move(nodeClass), move(position)) {}

RegexSyntaxTreeNode::RegexSyntaxTreeNode(RegexSyntaxTreeNode && other) noexcept : SyntaxTreeNode(move(other)) {
    nullableAttribute = other.nullableAttribute;
    firstposAttribute = move(other.firstposAttribute);
    lastposAttribute = move(other.lastposAttribute);
}


void RegexSyntaxTreeNode::calculateAttributes() {
    for(auto& ch : getChildren())
        dynamic_cast<RegexSyntaxTreeNode*>(ch)->calculateAttributes();

    nullableAttribute = false;
    firstposAttribute.clear();
    lastposAttribute.clear();
}

void RegexSyntaxTreeNode::calculatePositionAttributes(map<RegexSyntaxTreeNode *, set<RegexSyntaxTreeNode *>> & positions) {
    for(auto& ch : getChildren())
        dynamic_cast<RegexSyntaxTreeNode*>(ch)->calculatePositionAttributes(positions);
}

void NaN::calculateAttributes() {
    nullableAttribute = true;
    firstposAttribute.clear();
    lastposAttribute.clear();
}

void Concatenation::calculateAttributes() {
    RegexSyntaxTreeNode::calculateAttributes();

    nullableAttribute = first->getNullableAttribute() && second->getNullableAttribute();

    setInfuse(firstposAttribute, first->getFirstposAttribute());
    if(first->getNullableAttribute()) setInfuse(firstposAttribute, second->getFirstposAttribute());

    setInfuse(lastposAttribute, second->getFirstposAttribute());
    if(second->getNullableAttribute()) setInfuse(lastposAttribute, first->getFirstposAttribute());
}

void Concatenation::calculatePositionAttributes(map<RegexSyntaxTreeNode *, set<RegexSyntaxTreeNode *>> & positions) {
    RegexSyntaxTreeNode::calculatePositionAttributes(positions);

    for (auto i : first->getLastposAttribute()) {
        setInfuse(positions[i], second->getFirstposAttribute());
    }
}

void Character::calculateAttributes() {
    nullableAttribute = false;
    firstposAttribute.insert(this);
    lastposAttribute.insert(this);
}

void END::calculateAttributes() {
    nullableAttribute = false;
    firstposAttribute.insert(this);
    lastposAttribute.insert(this);
}

void Group::calculateAttributes() {
    RegexSyntaxTreeNode::calculateAttributes();

    nullableAttribute = node->getNullableAttribute();
    setInfuse(firstposAttribute, node->getFirstposAttribute());
    setInfuse(lastposAttribute, node->getLastposAttribute());
}

void Template::calculateAttributes() {
    throw indigo::Exception("regular-fsm::Template should not be asked to have attributes");
}

void Iteration::calculateAttributes() {
    RegexSyntaxTreeNode::calculateAttributes();

    nullableAttribute = true;
    setInfuse(firstposAttribute, node->getFirstposAttribute());
    setInfuse(lastposAttribute, node->getLastposAttribute());
}

void Iteration::calculatePositionAttributes(map<RegexSyntaxTreeNode *, set<RegexSyntaxTreeNode *>> & positions) {
    RegexSyntaxTreeNode::calculatePositionAttributes(positions);

    for (auto i : node->getLastposAttribute()) {
        setInfuse(positions[i], node->getFirstposAttribute());
    }
}

void PlusIteration::calculateAttributes() {
    RegexSyntaxTreeNode::calculateAttributes();

    nullableAttribute = node->getNullableAttribute();
    setInfuse(firstposAttribute, node->getFirstposAttribute());
    setInfuse(lastposAttribute, node->getLastposAttribute());
}

void PlusIteration::calculatePositionAttributes(map<RegexSyntaxTreeNode *, set<RegexSyntaxTreeNode *>> & positions) {
    RegexSyntaxTreeNode::calculatePositionAttributes(positions);

    for (auto i : node->getLastposAttribute()) {
        setInfuse(positions[i], node->getFirstposAttribute());
    }
}

void Option::calculateAttributes() {
    RegexSyntaxTreeNode::calculateAttributes();

    nullableAttribute = true;
    setInfuse(firstposAttribute, node->getFirstposAttribute());
    setInfuse(lastposAttribute, node->getLastposAttribute());
}

void Combination::calculateAttributes() {
    RegexSyntaxTreeNode::calculateAttributes();

    nullableAttribute = first->getNullableAttribute() || second->getNullableAttribute();

    setInfuse(firstposAttribute, first->getFirstposAttribute());
    setInfuse(firstposAttribute, second->getFirstposAttribute());

    setInfuse(lastposAttribute, first->getLastposAttribute());
    setInfuse(lastposAttribute, second->getLastposAttribute());
}

void Count::calculateAttributes() {
    RegexSyntaxTreeNode::calculateAttributes();

    nullableAttribute = minCount > 0 ? node->getNullableAttribute() : true;
    setInfuse(firstposAttribute, node->getFirstposAttribute());
    setInfuse(lastposAttribute, node->getLastposAttribute());
}

void Count::calculatePositionAttributes(map<RegexSyntaxTreeNode *, set<RegexSyntaxTreeNode *>> & positions) {
    RegexSyntaxTreeNode::calculatePositionAttributes(positions);

    if(!unlimited() && maxCount <= 0) return;  // no iterations may happen

    for (auto i : node->getLastposAttribute()) {
        setInfuse(positions[i], node->getFirstposAttribute());
    }
}
