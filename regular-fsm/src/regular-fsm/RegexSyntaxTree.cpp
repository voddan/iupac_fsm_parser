//
// Created by Daniil_Vodopian on 9/26/2017.
//

#include "RegexSyntaxTree.h"


RegexSyntaxTree::RegexSyntaxTree(const RegexSyntaxTreeNode & root) : SyntaxTree(root) {}

RegexSyntaxTree::~RegexSyntaxTree() {
    delete &followposAttribute;
}

void RegexSyntaxTree::calculateAttributes() {
    calculateNodeAttributes();
    calculatePositionAttributes();
}

void RegexSyntaxTree::calculateNodeAttributes() {

}

void RegexSyntaxTree::calculatePositionAttributes() {

}

StateMachine RegexSyntaxTree::buildStateMachine() {
    vector<StateMachine::State> states;
    return StateMachine(states);
}
