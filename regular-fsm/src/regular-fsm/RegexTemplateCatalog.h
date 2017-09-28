//
// Created by Daniil_Vodopian on 9/26/2017.
//

#ifndef IUPAC_FSM_PARSER_REGEXSYNTAXTREEBUILDER_H
#define IUPAC_FSM_PARSER_REGEXSYNTAXTREEBUILDER_H

#include <string>
#include <map>
#include "RegexSyntaxTree.h"

using std::string;
using std::map;

/**
 * Contains regex tamplaits, basic first.
 * A templaite may use an already addded templait 'myName' with %myName%
 * */
class RegexTemplateCatalog {
public:
    void addRegexTemplate(string nodeName, string regexTemplate);

    /**
     * Builds a tree with 'rootNodeName' as a root.
     * Name 'rootNodeName' must be added beforehand.
     * Also adds a terminal symbol to the end of the tree.
     * */
    RegexSyntaxTree buidRegexSyntaxTree(string rootNodeName);

private:
    map<string, string> & templateList = *new map<string, string>();
};


#endif //IUPAC_FSM_PARSER_REGEXSYNTAXTREEBUILDER_H
