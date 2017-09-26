//
// Created by Daniil_Vodopian on 9/26/2017.
//

#ifndef IUPAC_FSM_PARSER_SYNTAXTREE_H
#define IUPAC_FSM_PARSER_SYNTAXTREE_H

#include <vector>

using std::string;
using std::vector;

class SyntaxTree {
public:
    class Node {
    public:
        Node(const string & nodeClass, const TextPosition & origianalPosition);

        string prettyPrint(int indent = 0);

        void addChild(Node & child);

    public:
        const string nodeClass;
        const TextPosition origianalPosition;

    private:
        vector<Node> children;
    };
};

class TextPosition {
public:
    const string text;
    const int start;
    const int end;
};


#endif //IUPAC_FSM_PARSER_SYNTAXTREE_H
