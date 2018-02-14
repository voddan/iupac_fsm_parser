//
// Created by Daniil_Vodopian on 9/26/2017.
//

#ifndef IUPAC_FSM_PARSER_REGEXTEMPLATECATALOG_H
#define IUPAC_FSM_PARSER_REGEXTEMPLATECATALOG_H

#include <string>
#include <map>
#include <base_cpp/non_copyable.h>
#include "RegexSyntaxTree.h"

using std::string;
using std::map;

/**
 * Contains regex templates, basic first.
 * A template may use an already added template 'myName' with %myName%
 * */
class RegexTemplateCatalog : public indigo::NonCopyable {
public:
    RegexTemplateCatalog();
    RegexTemplateCatalog(RegexTemplateCatalog && other) noexcept;

    /**
     * Supports limited POSIX Extended regularExpressions
     * Unsupported features:
     *  - QUOTED_CHAR \^ \. \[ \$ \( \) \| \* \+ \? \{ \\
     *  - Bracket Expressions
     *  - Matching ends on a line with `^` and `$`
     *  - More than one digit in DUP_COUNT
     * */
    void addRegexTemplate(string nodeName, string regexTemplate);

    /**
     * A token string is a token or is a `|` separated list of tokens
     * Characters `.`, `+`, `&`, `,`, `;`, `?`, `*`, `(`, `)`, `[`, `]`, `-`, `{`, `}` do not need escaping
     * */
    void addTokenString(string nodeName, string tokenString);

    /**
     * Builds a tree with 'rootNodeName' as a root.
     * Name 'rootNodeName' must be added beforehand.
     * Also adds a terminal symbol to the end of the tree.
     * */
    RegexSyntaxTree buildRegexSyntaxTree(string rootNodeName);

    string prettyPrint();

private:
    map<string, string> templateStrings;
    map<string, string> tokenStrings;
    map<string, unique_ptr<RegexSyntaxTreeNode>> parsedTemplates;
};


#endif //IUPAC_FSM_PARSER_REGEXTEMPLATECATALOG_H
