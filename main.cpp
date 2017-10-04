#include <iostream>
#include <tinyxml.h>

#include <memory>
#include <vector>
#include <base_cpp/non_copyable.h>


using std::string;
using std::vector;
using std::move;
using std::cout;
using std::endl;

int main() {
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



    return 0;
}