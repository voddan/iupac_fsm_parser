//
// Created by Daniil_Vodopian on 9/26/2017.
//

#include "RegexTemplateCatalog.h"

void RegexTemplateCatalog::addRegexTemplate(string nodeName, string regexTemplate) {

}

RegexSyntaxTree RegexTemplateCatalog::buidRegexSyntaxTree(string rootNodeName) {
    RegexSyntaxTreeNode root("--", TextPosition{"", 0, 0});
    return RegexSyntaxTree(root);
}