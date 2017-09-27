//
// Created by Daniil_Vodopian on 9/26/2017.
//

#ifndef IUPAC_FSM_PARSER_STATEMACHINE_H
#define IUPAC_FSM_PARSER_STATEMACHINE_H

#include <string>
#include <set>
#include "SyntaxTree.h"

using std::string;
using std::set;

class StateMachine {
public:
    class State;
    class Transit;

    explicit StateMachine(vector<State> & states);

    SyntaxTree parse(string text) const;

public:
    class State {
    public:
        explicit State(bool final);

        const State & processInput(char input) const;

        void addTransit(Transit transit);

        const bool isFinal() const;

    private:
        const bool final;
        vector<Transit> transitions;
    };

    class Transit {
    public:
        Transit(const State & destination, const set<char> & charset);

        bool accepts(char input) const;

    public:
        const State & destination;
        const set<char> charset;
    };

private:
    const vector<State> states;
};


#endif //IUPAC_FSM_PARSER_STATEMACHINE_H
