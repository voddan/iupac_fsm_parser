//
// Created by Daniil_Vodopian on 9/27/2017.
//

#include "RegexSyntaxTreeNode.h"

#include <memory>


using std::move;

RegexSyntaxTreeNode::RegexSyntaxTreeNode(string nodeClass, TextPosition position) :
        SyntaxTreeNode(move(nodeClass), move(position)) {}

RegexSyntaxTreeNode::RegexSyntaxTreeNode(RegexSyntaxTreeNode && other) noexcept : SyntaxTreeNode(move(other)) {
    nullableAttribute = other.nullableAttribute;
    firstposAttribute = move(other.firstposAttribute);
    lastposAttribute = move(other.lastposAttribute);
}

void RegexSyntaxTreeNode::calculateAttributes() {

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