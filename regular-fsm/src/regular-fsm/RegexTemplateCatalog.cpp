//
// Created by Daniil_Vodopian on 9/26/2017.
//

#include "RegexTemplateCatalog.h"

#include <sstream>
#include <regex>
#include <memory>
#include <base_cpp/exception.h>


using std::move;
using std::endl;
vector<TextPosition> split(char delimiter, TextPosition position);

RegexTemplateCatalog::RegexTemplateCatalog() { }

RegexTemplateCatalog::RegexTemplateCatalog(RegexTemplateCatalog && other) noexcept {
    templateStrings = move(other.templateStrings);
    tokenStrings = move(other.tokenStrings);
    parsedTemplates = move(other.parsedTemplates);
}

void RegexTemplateCatalog::addRegexTemplate(string nodeName, string regexTemplate) {
    templateStrings[nodeName] = move(regexTemplate);
}

void RegexTemplateCatalog::addTokenString(string nodeName, string tokenString) {
    const vector<TextPosition> & branches = split('|', TextPosition(tokenString, 0));

    std::unique_ptr<RegexSyntaxTreeNode> root;
    for(auto& branch : branches) {
        RegexSyntaxTreeNode node = fromTrivialString(branch);
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

    for(auto& pair : tokenStrings) {
        string name = pair.first;
        string tokenString = pair.second;

        str << "<" << name << " tokenString=\"" << tokenString << "\">" << endl;

        auto iter = parsedTemplates.find(name);
        if(iter != parsedTemplates.end()) {
            RegexSyntaxTreeNode & parsed = iter->second;
            str << parsed.prettyPrint(1);
        } else {
            str << "\t<ERROR/>" << endl;
        }

        str << "</" << name << ">" << endl;
    }

    for(auto& pair : templateStrings) {
        string name = pair.first;
        string templateString = pair.second;

        str << "<" << name << " templateString=\"" << templateString << "\">" << endl;

        auto iter = parsedTemplates.find(name);
        if(iter != parsedTemplates.end()) {
            RegexSyntaxTreeNode & parsed = iter->second;
            str << parsed.prettyPrint(1);
        } else {
            str << "\t<ERROR/>" << endl;
        }

        str << "</" << name << ">" << endl;
    }

    return str.str();
}

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