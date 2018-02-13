//
// Created by Daniil_Vodopian on 9/27/2017.
//

#ifndef IUPAC_FSM_PARSER_TEXTPOSITION_H
#define IUPAC_FSM_PARSER_TEXTPOSITION_H

#include <string>
#include <base_cpp/exception.h>
#include <cassert>

using std::string;

/**
 * `TextPosition` represents a part of the original input string.
 *
 * Knowing the original input and the value `begin`,
 * one can trace any `TextPosition` instance back to its position in the input.
 * That can be used for precise error reporting.
 */
struct TextPosition {
    TextPosition(const string & text, string::size_type begin) :
            text(text), begin(begin), end(begin + text.length()) {}

    bool operator==(const TextPosition & other) {
        return text == other.text &&
                begin == other.begin &&
                end == other.end;
    };

    inline bool empty() {
        return begin == end;
    }

    const string text;
    const string::size_type begin;
    const string::size_type end;  // TODO: probably can be removed
};


#endif //IUPAC_FSM_PARSER_TEXTPOSITION_H
