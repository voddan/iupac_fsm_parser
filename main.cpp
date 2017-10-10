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

RegexSyntaxTreeNode testfromTrivialString(TextPosition position) {
    if(position.empty())
        return NaN(position.begin);

    ;
    std::unique_ptr<RegexSyntaxTreeNode> root(new Character(position.text[0], position.begin));

    auto ch = position.text.begin();
    auto pos = position.begin;
    for(ch++, pos++; pos != position.end; ch++, pos++) {
        Character character(*ch, pos);
        root.reset(new Concatenation(move(*root.release()), move(character)));
    }

    return move(*root.release());
}

int main() {
    string str("(ab|c?d+)*e");

    RegexTemplateCatalog catalog;
    catalog.addRegexTemplate("regex", "1(2|34)*5");

    std::cout << catalog.prettyPrint();

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