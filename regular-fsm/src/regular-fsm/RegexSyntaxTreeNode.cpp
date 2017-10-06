//
// Created by Daniil_Vodopian on 9/27/2017.
//

#include "RegexSyntaxTreeNode.h"

#include <bits/unique_ptr.h>


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

    Character firstCh(position.text[0], position.begin);
    std::unique_ptr<RegexSyntaxTreeNode> root(&firstCh);

    auto ch = position.text.begin();
    auto pos = position.begin;
    for(ch++, pos++ /* skips the first */; pos != position.end; ch++, pos++) {
        Character character(*ch, pos);
        Concatenation concatenation(move(*root.release()), move(character));
        root.reset(&concatenation);
    }

    return move(*root.release());
}