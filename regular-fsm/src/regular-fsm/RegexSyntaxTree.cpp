//
// Created by Daniil_Vodopian on 9/26/2017.
//

#include "RegexSyntaxTree.h"


using std::move;

RegexSyntaxTree::RegexSyntaxTree(RegexSyntaxTreeNode root) : SyntaxTree(move(root)) {}

RegexSyntaxTree::RegexSyntaxTree(RegexSyntaxTree && other) noexcept : SyntaxTree(move(other)) {
    followposAttribute = move(other.followposAttribute);
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
    StateMachine::State s1(true);
    StateMachine::State s2(true);

    vector<StateMachine::State> states;
    states.push_back(move(s1));
    states.push_back(move(s2));

    StateMachine machine(move(states));
    return move(machine);
}
