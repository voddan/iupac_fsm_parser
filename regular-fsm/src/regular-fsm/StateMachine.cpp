//
// Created by Daniil_Vodopian on 9/26/2017.
//

#include <base_cpp/exception.h>
#include "StateMachine.h"

StateMachine::StateMachine(const vector<State> & states) : states(states) {}

SyntaxTree StateMachine::parse(string str) const {
    SyntaxTreeNode root("--", TextPosition{"", 0, 0});
    return SyntaxTree(root);
}

StateMachine::State::State(bool final) : final(final) {}

StateMachine::State::~State() {
    delete &transitions;
}

const StateMachine::State & StateMachine::State::processInput(char input) const {
    for(auto trans : transitions) {
        if(trans.accepts(input))
            return trans.getDestination();
    }

    throw indigo::Exception("Input '%c' cannot be processed", input);
}

void StateMachine::State::addTransit(Transit transit) {
    transitions.push_back(transit);
}

bool StateMachine::State::isFinal() const {
    return final;
}

StateMachine::Transit::Transit(
        const StateMachine::State & destination,
        const set<char> & charset) :
        destination(destination), charset(charset) {}

bool StateMachine::Transit::accepts(char input) const {
    return charset.find(input) != charset.end();
}
