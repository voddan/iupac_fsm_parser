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

/**
 * A stack-less FSA (a.k.a Finite State Automata) that parses text char-by-char.
 */
class StateMachine : public indigo::NonCopyable {
public:
    class State;
    class Transit;

    explicit StateMachine(vector<State> states);
    StateMachine(StateMachine && other) noexcept;

    /**
     * Parse `text` into a syntax tree by running this FSA
     */
    SyntaxTree parse(string text) const;

private:
    const vector<State> states;

public:
    /**
     * A state of a FSA
     */
    class State : public indigo::NonCopyable {
    public:
        explicit State(bool final);
        State(State && other) noexcept;

        const State & processInput(char input) const;

        void addTransit(Transit transit);

        /**
         * An input string can end only in a final state to be accepted by the FSA.
         *
         * @return true if the state is marked as final
         */
        bool isFinal() const;

    private:
        const bool final;
        vector<Transit> transitions;
    };

    /**
     * A transitioning link between 2 states of the FSA
     *
     * To maintain determinism, any state CANNOT have two links
     * from it that accept the same character
     */
    class Transit : public indigo::NonCopyable {
    public:
        Transit(const State & destination, set<char> charset);
        Transit(Transit && other) noexcept;

        /**
         * @return true if the link can accept `input`
         * and transition from its state to `destination`
         */
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
