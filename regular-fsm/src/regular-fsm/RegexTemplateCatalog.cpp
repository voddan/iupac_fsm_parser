//
// Created by Daniil_Vodopian on 9/26/2017.
//

#include "RegexTemplateCatalog.h"

#include <sstream>
#include <regex>
#include <base_cpp/exception.h>


using std::move;
using std::endl;

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
    std::unique_ptr<RegexSyntaxTreeNode> root;

    std::regex firstRegex("([^|]+)\\|?");
    std::smatch firstMatches;

    if(std::regex_search(tokenString, firstMatches, firstRegex)) {
        auto match = firstMatches[1];
        RegexSyntaxTreeNode node = fromTrivialString(TextPosition(match, 0));
        root.reset(&node);
    } else {
        NaN nan(0);
        root.reset(&nan);
    }

    std::regex regex("\\|([^|]+)");
    std::smatch matches;

    string::const_iterator begin = tokenString.begin();
    const string::const_iterator end = tokenString.end();

    while(std::regex_search(begin, end, matches, regex)) {
        auto match = matches[1];
        RegexSyntaxTreeNode node = fromTrivialString(TextPosition(match, 0));
        Combination combination(move(*root.release()), move(node));
        root.reset(&combination);
        begin = match.second;  // shifts the search to the next match
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

        str << "%" << name << "% : " << tokenString << endl;

        auto iter = parsedTemplates.find(name);
        if(iter != parsedTemplates.end()) {
            RegexSyntaxTreeNode & parsed = iter->second;
            str << parsed.prettyPrint(1);
        } else {
            str << "\tERROR" << endl;
        }
    }

    for(auto& pair : templateStrings) {
        string name = pair.first;
        string templateString = pair.second;

        str << "%" << name << "% : " << templateString << endl;

        auto iter = parsedTemplates.find(name);
        if(iter != parsedTemplates.end()) {
            RegexSyntaxTreeNode & parsed = iter->second;
            str << parsed.prettyPrint(1);
        } else {
            str << "\tERROR" << endl;
        }
    }

    return str.str();
}
