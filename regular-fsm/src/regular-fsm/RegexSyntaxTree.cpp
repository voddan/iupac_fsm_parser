//
// Created by Daniil_Vodopian on 9/26/2017.
//

#include "RegexSyntaxTree.h"


RegexSyntaxTree::RegexSyntaxTree(RegexSyntaxTreeNode & root) : SyntaxTree(root) {}

void RegexSyntaxTree::calculateAttributes() {

}

void RegexSyntaxTree::calculateNodeAttributes() {

}

void RegexSyntaxTree::calculatePositionAttributes() {

}

StateMachine RegexSyntaxTree::buildStateMachine() {
    vector<StateMachine::State> states;
    return StateMachine(states);
}
