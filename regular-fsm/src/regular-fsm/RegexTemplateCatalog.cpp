//
// Created by Daniil_Vodopian on 9/26/2017.
//

#include "RegexTemplateCatalog.h"

#include <sstream>
#include <regex>
#include <memory>
#include <base_cpp/exception.h>
#include "RegexParsers.h"


using std::move;
using std::endl;
vector<TextPosition> split(char delimiter, TextPosition position);

RegexTemplateCatalog::RegexTemplateCatalog() { }

RegexTemplateCatalog::RegexTemplateCatalog(RegexTemplateCatalog && other) noexcept {
    templateStrings = move(other.templateStrings);
    tokenStrings = move(other.tokenStrings);
    parsedTemplates = move(other.parsedTemplates);
}

/**
 * Grammar used:
 *
 * extended_reg_exp   -> ERE_branch .
 * extended_reg_exp   -> extended_reg_exp `|` ERE_branch .
 *
 * ERE_branch         -> ERE_expression .
 * ERE_branch         -> ERE_branch ERE_expression .
 *
 * ERE_expression     -> ORD_CHAR .
 * ERE_expression     -> `(` extended_reg_exp `)` .
 * ERE_expression     -> `%` template_name `%` .
 * ERE_expression     -> ORD_CHAR ERE_dupl_symbol.
 * ERE_expression     -> `(` extended_reg_exp `)` ERE_dupl_symbol.
 * ERE_expression     -> `%` template_name `%` ERE_dupl_symbol.
 *
 * ERE_dupl_symbol    -> `*` .
 * ERE_dupl_symbol    -> `+` .
 * ERE_dupl_symbol    -> `?` .
 * ERE_dupl_symbol    -> `{` DUP_COUNT               `}` .
 * ERE_dupl_symbol    -> `{` DUP_COUNT `,`           `}` .
 * ERE_dupl_symbol    -> `{` DUP_COUNT `,` DUP_COUNT `}` .
 * */
void RegexTemplateCatalog::addRegexTemplate(string nodeName, string regexTemplate) {
    auto node = parse_extended_reg_exp(TextPosition(regexTemplate, 0));

    templateStrings[nodeName] = move(regexTemplate);

    Group group(nodeName, move(node));
    parsedTemplates.insert(std::pair<string, RegexSyntaxTreeNode>(nodeName, move(group)));
}

void RegexTemplateCatalog::addTokenString(string nodeName, string tokenString) {
    const vector<TextPosition> & branches = split('|', TextPosition(tokenString, 0));

    std::unique_ptr<RegexSyntaxTreeNode> root;
    for(auto& branch : branches) {
        RegexSyntaxTreeNode node = parse_trivial_string(branch);
        if(root)
            root.reset(new Combination(move(*root.release()), move(node)));
        else
            root.reset(new RegexSyntaxTreeNode(move(node)));
    }

    tokenStrings[nodeName] = move(tokenString);

    Group group(nodeName, move(*root.release()));
    parsedTemplates.insert(std::pair<string, RegexSyntaxTreeNode>(nodeName, move(group)));
}

RegexSyntaxTree RegexTemplateCatalog::buildRegexSyntaxTree(string rootNodeName) {
    const auto iterator = templateStrings.find(rootNodeName);
    if(iterator == templateStrings.end())
        throw indigo::Exception("Invalid root node name %s", rootNodeName.c_str());

    string rootName = iterator->first;
    string rootTemplate = iterator->second;


    RegexSyntaxTreeNode root(rootName, TextPosition(rootTemplate, 0));


    RegexSyntaxTree tree(move(root));
    return move(tree);
}

string RegexTemplateCatalog::prettyPrint() {
    std::ostringstream str;

    str << "<catalog>" << endl;

    for(auto& pair : tokenStrings) {
        string name = pair.first;
        string tokenString = pair.second;

        str << "\t<" << name << " tokenString=\"" << tokenString << "\">" << endl;

        auto iter = parsedTemplates.find(name);
        if(iter != parsedTemplates.end()) {
            RegexSyntaxTreeNode & parsed = iter->second;
            str << parsed.prettyPrint(2);
        } else {
            str << "\t\t<ERROR/>" << endl;
        }

        str << "\t</" << name << ">" << endl;
    }

    for(auto& pair : templateStrings) {
        string name = pair.first;
        string templateString = pair.second;

        str << "\t<" << name << " templateString=\"" << templateString << "\">" << endl;

        auto iter = parsedTemplates.find(name);
        if(iter != parsedTemplates.end()) {
            RegexSyntaxTreeNode & parsed = iter->second;
            str << parsed.prettyPrint(2);
        } else {
            str << "\t\t<ERROR/>" << endl;
        }

        str << "\t</" << name << ">" << endl;
    }

    str << "</catalog>" << endl;

    return str.str();
}
