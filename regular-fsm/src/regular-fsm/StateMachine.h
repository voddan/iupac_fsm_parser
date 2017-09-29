//
// Created by Daniil_Vodopian on 9/26/2017.
//

#ifndef IUPAC_FSM_PARSER_STATEMACHINE_H
#define IUPAC_FSM_PARSER_STATEMACHINE_H

#include <string>
#include <set>
#include <base_cpp/non_copyable.h>
#include "SyntaxTree.h"

using std::string;
using std::set;

class StateMachine : public indigo::NonCopyable {
public:
    class State;
    class Transit;

    explicit StateMachine(vector<State> states);
    StateMachine(StateMachine && other) noexcept;

    SyntaxTree parse(string text) const;

private:
    const vector<State> states;

public:
    class State : public indigo::NonCopyable {
    public:
        explicit State(bool final);
        State(State && other) noexcept;

        const State & processInput(char input) const;

        void addTransit(Transit transit);

        bool isFinal() const;

    private:
        const bool final;
        vector<Transit> transitions;
    };

    class Transit : public indigo::NonCopyable {
    public:
        Transit(const State & destination, set<char> charset);
        Transit(Transit && other) noexcept;

        bool accepts(char input) const;

        inline const State & getDestination() const {
            return destination;
        }

    private:
        const State & destination;
        const set<char> charset;
    };
};




#endif //IUPAC_FSM_PARSER_STATEMACHINE_H
