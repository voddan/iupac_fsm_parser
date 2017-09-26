#include <iostream>
#include <tinyxml.h>
#include <regular-fsm/RegexTemplateCatalog.h>
#include <regular-fsm/RegexSyntaxTree.h>

#include <base_c/bitarray.h>

int main() {
    TiXmlDocument doc("C:\\Users\\Daniil_Vodopian\\Documents\\Indigo\\iupac-fsm-parser\\grammar\\alkanes.xml");
    doc.LoadFile();

    fprintf(stdout, "hello");

    doc.Print(stdout, 0);

    return 0;
}