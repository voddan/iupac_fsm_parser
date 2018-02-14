#include <iostream>
#include <tinyxml.h>

#include <memory>
#include <vector>
#include <regex>
#include <memory>
#include <utility>
#include <base_cpp/non_copyable.h>
#include <regular-fsm/RegexSyntaxTreeNode.h>
#include <regular-fsm/RegexTemplateCatalog.h>


void print_all_tokens_from_xml_files() ;

using std::string;
using std::vector;
using std::move;
using std::cout;
using std::endl;
using std::make_unique;


int main() {
    string str("(ab|c?d+)*e");
    // (a|b)*abb#
    // 0123456789

    RegexTemplateCatalog catalog;
    catalog.addRegexTemplate("regex", "1(2|34)*5");
    auto n1 = make_unique<Character>('a', 1);
    auto n2 = make_unique<Character>('b', 3);
    auto n3 = make_unique<Character>('a', 6);
    auto n4 = make_unique<Character>('b', 7);
    auto n5 = make_unique<Character>('b', 8);
    auto n6 = make_unique<END>(9);

    std::cout << catalog.prettyPrint();
    auto q1 = make_unique<Combination>(move(n1), move(n2));     // a|b
    auto q2 = make_unique<Group>(move(q1));                     // (a|b)
    auto q3 = make_unique<Iteration>(move(q2));                 // (a|b)*
    auto q4 = make_unique<Concatenation>(move(q3), move(n3));   // (a|b)*a
    auto q5 = make_unique<Concatenation>(move(q4), move(n4));   // (a|b)*ab
    auto q6 = make_unique<Concatenation>(move(q5), move(n5));   // (a|b)*abb
    auto q7 = make_unique<Concatenation>(move(q6), move(n6));   // (a|b)*abb

    RegexSyntaxTree tree(move(q7));
    tree.calculateAttributes();

    return 0;
}


void print_all_tokens_from_xml_files() {
    string grammarPath ("C:\\Users\\Daniil_Vodopian\\Documents\\Indigo\\iupac-fsm-parser\\grammar\\");

    TiXmlDocument indexFile((grammarPath + "index.xml").c_str());
    indexFile.LoadFile();

    TiXmlNode * tokenFiles = indexFile.FirstChild("tokenFiles");
    TiXmlNode * tokenFile = tokenFiles->FirstChild("tokenFile");

    vector<string> xmlFileNames;
    while(tokenFile) {
        TiXmlNode * value = tokenFile->FirstChild();
        xmlFileNames.push_back(value->ValueTStr());
        tokenFile = tokenFiles->IterateChildren("tokenFile", tokenFile);
    }

    for(auto& fileName : xmlFileNames) {
        cout << fileName << endl;
        TiXmlDocument tokenListsFile((grammarPath + fileName).c_str());
        tokenListsFile.LoadFile();

        TiXmlNode * tokenLists = tokenListsFile.FirstChild("tokenLists");
        TiXmlNode * tokenList = (tokenLists) ?
                                tokenLists->FirstChild("tokenList") :
                                tokenListsFile.FirstChild("tokenList");

        while(tokenList) {
            TiXmlNode * token = tokenList->FirstChild("token");
            while(token) {
                TiXmlNode * value = token->FirstChild();

                if(value) {
                    cout << "\t" << *value << endl;
                } else {
                    cout << endl;
                }

                token = tokenList->IterateChildren("token", token);
            }

            tokenList = (tokenLists) ? tokenLists->IterateChildren("tokenList", tokenList) : nullptr;
        }
    }
}