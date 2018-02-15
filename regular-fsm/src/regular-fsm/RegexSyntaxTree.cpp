//
// Created by Daniil_Vodopian on 9/26/2017.
//

#include "RegexSyntaxTree.h"


using std::move;

RegexSyntaxTree::RegexSyntaxTree(unique_ptr<RegexSyntaxTreeNode> root) : SyntaxTree(move(root)) {}

RegexSyntaxTree::RegexSyntaxTree(RegexSyntaxTree && other) noexcept : SyntaxTree(move(other)) {
    followposAttribute = move(other.followposAttribute);
}

void RegexSyntaxTree::calculateAttributes() {
    // The order is essential!
    calculateNodeAttributes();
    calculatePositionAttributes();
}

void RegexSyntaxTree::calculateNodeAttributes() {
    dynamic_cast<RegexSyntaxTreeNode*>(root.get())->calculateAttributes();
}

void RegexSyntaxTree::calculatePositionAttributes() {
    dynamic_cast<RegexSyntaxTreeNode*>(root.get())->calculatePositionAttributes(followposAttribute);
}

StateMachine RegexSyntaxTree::buildStateMachine() {
    StateMachine::State s1(true);
    StateMachine::State s2(true);

    vector<StateMachine::State> states;
    states.push_back(move(s1));
    states.push_back(move(s2));

    StateMachine machine(move(states));
    return move(machine);
}
