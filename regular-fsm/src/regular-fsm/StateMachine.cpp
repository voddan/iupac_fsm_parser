//
// Created by Daniil_Vodopian on 9/26/2017.
//

#include "StateMachine.h"


#include <base_cpp/exception.h>

using std::move;

StateMachine::StateMachine(vector<State> states) : states(move(states)) {}

StateMachine::StateMachine(StateMachine && other) noexcept : states((vector<State> &&) other.states) {}

//TODO: implement
SyntaxTree StateMachine::parse(string str) const {
    // Dummy implementation
    SyntaxTree tree(std::make_unique<SyntaxTreeNode>("--", TextPosition{"", 0}));
    return tree;
}


StateMachine::State::State(bool final) : final(final) {}

StateMachine::State::State(State&& other) noexcept : final(other.final) {
    transitions = move(other.transitions);
}

const StateMachine::State & StateMachine::State::processInput(char input) const {
//    for(auto& trans : transitions) {  // a CLion 2017.2.2 bug
    for(const Transit & trans : transitions) {
        if(trans.accepts(input))
            return trans.getDestination();
    }

    throw indigo::Exception("Input '%c' cannot be processed", input);
}

void StateMachine::State::addTransit(Transit transit) {
    transitions.push_back(move(transit));
}

bool StateMachine::State::isFinal() const {
    return final;
}


StateMachine::Transit::Transit(const State & destination, set<char> charset) :
        destination(destination), charset(move(charset)) {}

StateMachine::Transit::Transit(Transit && other) noexcept :
        destination(other.destination), charset(other.charset) {}

bool StateMachine::Transit::accepts(char input) const {
    return charset.find(input) != charset.end();
}
