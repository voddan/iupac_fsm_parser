#include <iostream>
#include <tinyxml.h>

#include <memory>
#include <vector>
#include <regex>
#include <base_cpp/non_copyable.h>


void print_all_tokens_from_xml_files() ;

using std::string;
using std::vector;
using std::move;
using std::cout;
using std::endl;

int main() {
//    string tokenString("l-tartrate|(l*)-tartrate|l(+?)-tartrate|l-(+)-tartrate|l.tartrat|(l)-ta rtrat|l( +)-tartrat|l-(+)-tartrat");
    string tokenString("l-tartrate|");
//    string tokenString("");

    std::regex firstRegex("([^|]+)\\|?");
    std::smatch firstMatches;

    if(std::regex_search(tokenString, firstMatches, firstRegex)) {
        auto match = firstMatches[1];
        cout << match << endl;
    }

    std::regex regex("\\|([^|]+)");
    std::smatch matches;

    string::const_iterator begin = tokenString.begin();
    const string::const_iterator end = tokenString.end();

    while(std::regex_search(begin, end, matches, regex)) {
        auto match = matches[1];
        cout << match << endl;
        begin = match.second;
    }



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