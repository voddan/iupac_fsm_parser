//
// Created by Daniil_Vodopian on 10/3/2017.
//

#include <catch.hpp>
#include <regular-fsm/RegexTemplateCatalog.h>

TEST_CASE("Single regex") {
    RegexTemplateCatalog catalog;
    catalog.addRegexTemplate("chemical", "H2O");
    const RegexSyntaxTree & tree = catalog.buildRegexSyntaxTree("chemical");
    
    CHECK(tree.prettyPrint() == "NOT IMPLEMENTED");  // TODO: add test
}

TEST_CASE("Substituting one template") {
    RegexTemplateCatalog catalog;
    catalog.addRegexTemplate("water", "H2O");
    catalog.addRegexTemplate("mater", "CO2%water%CO2");
    const RegexSyntaxTree & tree = catalog.buildRegexSyntaxTree("mater");
    
    RegexTemplateCatalog _catalog;
    _catalog.addRegexTemplate("mater", "CO2H2OCO2");
    const RegexSyntaxTree & _tree = _catalog.buildRegexSyntaxTree("mater");
    
    CHECK(tree.prettyPrint() == _tree.prettyPrint());
}

TEST_CASE("Several templates") {
    RegexTemplateCatalog catalog;
    catalog.addRegexTemplate("oxygen", "O");
    catalog.addRegexTemplate("water", "H2%oxygen%");
    catalog.addRegexTemplate("nitro", "N%oxygen%");
    catalog.addRegexTemplate("mater", "CO2%oxygen%%water%C%oxygen%2");
    catalog.addRegexTemplate("chemical", "%water%%oxygen%");
    const RegexSyntaxTree & tree = catalog.buildRegexSyntaxTree("mater");

    RegexTemplateCatalog _catalog;
    _catalog.addRegexTemplate("mater", "CO2OH2OCO2");
    const RegexSyntaxTree & _tree = _catalog.buildRegexSyntaxTree("mater");

    CHECK(tree.prettyPrint() == _tree.prettyPrint());
}