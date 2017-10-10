//
// Created by Daniil_Vodopian on 10/10/2017.
//

#include "RegexParsers.h"

#include <regex>
#include <memory>
#include <iostream>

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

template <typename JOINT>
void hang_up_to_the_root(std::unique_ptr<RegexSyntaxTreeNode> & root, RegexSyntaxTreeNode node) {
    if(root)
        root.reset(new JOINT(move(*root.release()), move(node)));
    else
        root.reset(new RegexSyntaxTreeNode(move(node)));
}

RegexSyntaxTreeNode parse_extended_reg_exp(TextPosition position) {
    vector<TextPosition> branches;

    const string::const_iterator begin = position.text.begin();
    const string::const_iterator end = position.text.end();
    auto iter = begin;

    int nestingLevel = 0;
    for(auto i = begin; i < end; i++) {
        if('(' == *i){
            nestingLevel++;
        } else if(')' == *i) {
            nestingLevel--;
        } else if('|' == *i && 0 == nestingLevel) {
            branches.emplace_back(string(iter, i), iter - begin + position.begin);
            iter = i + 1;
        }
    }
    branches.emplace_back(string(iter, end), iter - begin + position.begin);


    //-------------------------------------

    std::unique_ptr<RegexSyntaxTreeNode> root;

    for(auto& branch : branches) {
        RegexSyntaxTreeNode node = parse_ERE_branch(branch);
        hang_up_to_the_root<Combination>(root, move(node));
    }

    return move(*root.release());
}

RegexSyntaxTreeNode parse_ERE_branch(TextPosition position) {
//                   01   2  2     3  3             14         5  5   4 0
    std::regex regex("(\\((.*)\\)|%(.+)%|[^(){}%*+?])([*+?]|\\{(.*)\\})?");
    std::smatch matches;
    
    std::unique_ptr<RegexSyntaxTreeNode> root;

    const string::const_iterator begin = position.text.begin();
    const string::const_iterator end = position.text.end();
    auto iter = begin;

    while(std::regex_search(iter, end, matches, regex, std::regex_constants::match_continuous)) {
        std::unique_ptr<RegexSyntaxTreeNode> expression;

        if(matches[2].matched) {
            auto match = matches[2];
            auto node = parse_extended_reg_exp(TextPosition(match.str(), match.first - begin + position.begin));
            expression.reset(new RegexSyntaxTreeNode(move(node)));
        } else if(matches[3].matched) {
            auto match = matches[3];
            auto node = Template(TextPosition(match.str(), match.first - begin + position.begin));
            expression.reset(new RegexSyntaxTreeNode(move(node)));
        } else {
            auto match = matches[1];
            auto node = Character(*match.first, match.first - begin + position.begin);
            expression.reset(new RegexSyntaxTreeNode(move(node)));
        }

        if(matches[4].matched) {
            auto match = matches[4];
            auto node = parse_ERE_dupl_symbol(
                    TextPosition(match.str(), match.first - begin + position.begin),
                    move(*expression.release()));
            expression.reset(new RegexSyntaxTreeNode(move(node)));
        }

        hang_up_to_the_root<Concatenation>(root, move(*expression.release()));
        iter = matches[0].second;
    }

    if(root)
        return move(*root.release());
    else
        return move(NaN(position.begin));
}

RegexSyntaxTreeNode parse_ERE_dupl_symbol(TextPosition position, RegexSyntaxTreeNode previous) {
//                   0           1    1    2     34    4    3 2  0
    std::regex regex("[*+?]|\\{\\s*(\\d+)\\s*(,\\s*((\\d+)\\s*)?)?\\}");
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

RegexSyntaxTreeNode parse_trivial_string(TextPosition position) {
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
