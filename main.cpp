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


int main() {
    string str("(ab|c?d+)*e");
    // (a|b)*abb#
    // 0123456789

    RegexTemplateCatalog catalog;
    catalog.addRegexTemplate("regex", "1(2|34)*5");
    Character n1('a', 1);
    Character n2('b', 3);
    Character n3('a', 6);
    Character n4('b', 7);
    Character n5('b', 8);
    END n6(9);

    std::cout << catalog.prettyPrint();
    Combination q1(move(n1), move(n2));     // a|b
    Group q2(move(q1));                     // (a|b)
    Iteration q3(move(q2));                 // (a|b)*
    Concatenation q4(move(q3), move(n3));   // (a|b)*a
    Concatenation q5(move(q4), move(n4));   // (a|b)*ab
    Concatenation q6(move(q5), move(n5));   // (a|b)*abb
    Concatenation q7(move(q6), move(n6));   // (a|b)*abb

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