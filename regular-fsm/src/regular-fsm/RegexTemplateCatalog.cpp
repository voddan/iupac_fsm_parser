//
// Created by Daniil_Vodopian on 9/26/2017.
//

#include "RegexTemplateCatalog.h"


using std::move;

RegexTemplateCatalog::RegexTemplateCatalog() { }

RegexTemplateCatalog::RegexTemplateCatalog(RegexTemplateCatalog && other) noexcept {
    templateList = move(other.templateList);
}

void RegexTemplateCatalog::addRegexTemplate(string nodeName, string regexTemplate) {
    templateList[nodeName] = move(regexTemplate);
}

RegexSyntaxTree RegexTemplateCatalog::buildRegexSyntaxTree(string rootNodeName) {
    RegexSyntaxTreeNode root("--", TextPosition{"", 0, 0});
    RegexSyntaxTree tree(move(root));
    return move(tree);
}
