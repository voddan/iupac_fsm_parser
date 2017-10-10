//
// Created by Daniil_Vodopian on 10/10/2017.
//

#include "RegexParsers.h"

#include <regex>
#include <memory>

vector<TextPosition> split(char delimiter, TextPosition position) {
    string D(1, delimiter);
    vector<TextPosition> results;

    std::regex firstRegex("([^" + D + "]*)[" + D + "]?");
    std::smatch firstMatches;

    if(std::regex_search(position.text, firstMatches, firstRegex)) {
        auto match = firstMatches[1];
        results.emplace_back(match, 0);
    }

    std::regex regex("[" + D + "]([^" + D +  "]*)");
    std::smatch matches;

    const string::const_iterator begin = position.text.begin();
    const string::const_iterator end = position.text.end();
    auto iter = begin;

    while(std::regex_search(iter, end, matches, regex)) {
        auto match = matches[1];
        results.emplace_back(match, match.first - begin);
        iter = match.second;  // shifts the search to the next match
    }

    return results;
}

RegexSyntaxTreeNode parse_ERE_dupl_symbol(TextPosition position, RegexSyntaxTreeNode previous) {
//                   0           1    1    2     34    4    3 2  0
    std::regex regex("[*+?]|{\\s*(\\d+)\\s*(,\\s*((\\d+)\\s*)?)?}");
    std::smatch matches;

    if(!std::regex_match(position.text, matches, regex))
        return NaN(position.begin);

    if(matches[1].matched) {  // {\d+(,(\d+)?)?}
        int minCount = std::stoi(matches[1]);
        if(matches[2].matched) {
            if(matches[4].matched) {
                int maxCount = std::stoi(matches[4]);
                return Count(move(previous), position, minCount, maxCount);
            } else {
                return Count(move(previous), position, minCount);
            }
        } else {
            return Count(move(previous), position, minCount, minCount);
        }
    } else {  // [*+?]
        char ch = *matches[0].first;
        if('*' == ch)
            return Iteration(move(previous));
        else if('+' == ch)
            return PlusIteration(move(previous));
        else
            return Option(move(previous));
    }
}

RegexSyntaxTreeNode fromTrivialString(TextPosition position) {
    if(position.empty())
        return NaN(position.begin);

    std::unique_ptr<RegexSyntaxTreeNode> root(new Character(position.text[0], position.begin));


    auto ch = position.text.begin();
    auto pos = position.begin;
    for(ch++, pos++ /* skips the first */; pos != position.end; ch++, pos++) {
        Character character(*ch, pos);
        root.reset(new Concatenation(move(*root.release()), move(character)));
    }

    return move(*root.release());
}