//
// Created by Daniil_Vodopian on 9/27/2017.
//

#ifndef IUPAC_FSM_PARSER_TEXTPOSITION_H
#define IUPAC_FSM_PARSER_TEXTPOSITION_H

#include <string>
#include <base_cpp/exception.h>
#include <cassert>

using std::string;

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
    const string::size_type end;
};


#endif //IUPAC_FSM_PARSER_TEXTPOSITION_H
