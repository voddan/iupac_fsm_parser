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
    TextPosition(const string & text, string::size_type begin, string::size_type end) :
            text(text), begin(begin), end(end) {
        assert(text.length() == end - begin);
    }

    TextPosition(const string & text, string::size_type begin) :
            TextPosition(text, begin, begin + text.length()) {}

    TextPosition(const string & text) : TextPosition(text, 0) {}

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
