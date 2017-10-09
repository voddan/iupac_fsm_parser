//
// Created by Daniil_Vodopian on 10/3/2017.
//

#include <catch.hpp>
#include <iostream>
#include <regular-fsm/RegexTemplateCatalog.h>

TEST_CASE("Parse one token string, one token") {
    RegexTemplateCatalog catalog;
    catalog.addTokenString("chemical", "H2O");

    const char * catalogStr =
            "<chemical tokenString=\"H2O\">\n"
            "\t<chemical text=\"(H2O)\">\n"
            "\t\t<CAT text=\"H2O\">\n"
            "\t\t\t<CAT text=\"H2\">\n"
            "\t\t\t\t<CH text=\"H\"/>\n"
            "\t\t\t\t<CH text=\"2\"/>\n"
            "\t\t\t</CAT>\n"
            "\t\t\t<CH text=\"O\"/>\n"
            "\t\t</CAT>\n"
            "\t</chemical>\n"
            "</chemical>\n";

    CHECK(catalog.prettyPrint() == catalogStr);
}

TEST_CASE("Parse one token string, multiple tokens") {
    RegexTemplateCatalog catalog;
    catalog.addTokenString("chemical", "l-tartrate|(l*)-tartrate|l(+?)-tartrate|l-(+)-tartrate|l.tartrat|(l)-ta rtrat|l( +)-tartrat");

    const char * catalogStr =
            "<chemical tokenString=\"l-tartrate|(l*)-tartrate|l(+?)-tartrate|l-(+)-tartrate|l.tartrat|(l)-ta rtrat|l( +)-tartrat\">\n"
            "\t<chemical text=\"(l-tartrate|(l*)-tartrate|l(+?)-tartrate|l-(+)-tartrate|l.tartrat|(l)-ta rtrat|l( +)-tartrat)\">\n"
            "\t\t<COMB text=\"l-tartrate|(l*)-tartrate|l(+?)-tartrate|l-(+)-tartrate|l.tartrat|(l)-ta rtrat|l( +)-tartrat\">\n"
            "\t\t\t<COMB text=\"l-tartrate|(l*)-tartrate|l(+?)-tartrate|l-(+)-tartrate|l.tartrat|(l)-ta rtrat\">\n"
            "\t\t\t\t<COMB text=\"l-tartrate|(l*)-tartrate|l(+?)-tartrate|l-(+)-tartrate|l.tartrat\">\n"
            "\t\t\t\t\t<COMB text=\"l-tartrate|(l*)-tartrate|l(+?)-tartrate|l-(+)-tartrate\">\n"
            "\t\t\t\t\t\t<COMB text=\"l-tartrate|(l*)-tartrate|l(+?)-tartrate\">\n"
            "\t\t\t\t\t\t\t<COMB text=\"l-tartrate|(l*)-tartrate\">\n"
            "\t\t\t\t\t\t\t\t<CAT text=\"l-tartrate\">\n"
            "\t\t\t\t\t\t\t\t\t<CAT text=\"l-tartrat\">\n"
            "\t\t\t\t\t\t\t\t\t\t<CAT text=\"l-tartra\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"l-tartr\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"l-tart\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"l-tar\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"l-ta\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"l-t\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"l-\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"l\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"-\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"t\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"a\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"r\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"t\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"r\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t<CH text=\"a\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t<CH text=\"t\"/>\n"
            "\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t<CH text=\"e\"/>\n"
            "\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t<CAT text=\"(l*)-tartrate\">\n"
            "\t\t\t\t\t\t\t\t\t<CAT text=\"(l*)-tartrat\">\n"
            "\t\t\t\t\t\t\t\t\t\t<CAT text=\"(l*)-tartra\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"(l*)-tartr\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"(l*)-tart\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"(l*)-tar\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"(l*)-ta\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"(l*)-t\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"(l*)-\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"(l*)\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"(l*\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"(l\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"(\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"l\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"*\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\")\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"-\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"t\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"a\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"r\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"t\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"r\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t<CH text=\"a\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t<CH text=\"t\"/>\n"
            "\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t<CH text=\"e\"/>\n"
            "\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t</COMB>\n"
            "\t\t\t\t\t\t\t<CAT text=\"l(+?)-tartrate\">\n"
            "\t\t\t\t\t\t\t\t<CAT text=\"l(+?)-tartrat\">\n"
            "\t\t\t\t\t\t\t\t\t<CAT text=\"l(+?)-tartra\">\n"
            "\t\t\t\t\t\t\t\t\t\t<CAT text=\"l(+?)-tartr\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"l(+?)-tart\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"l(+?)-tar\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"l(+?)-ta\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"l(+?)-t\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"l(+?)-\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"l(+?)\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"l(+?\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"l(+\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"l(\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"l\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"(\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"+\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"?\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\")\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"-\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"t\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"a\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"r\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"t\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t<CH text=\"r\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t<CH text=\"a\"/>\n"
            "\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t<CH text=\"t\"/>\n"
            "\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t<CH text=\"e\"/>\n"
            "\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t</COMB>\n"
            "\t\t\t\t\t\t<CAT text=\"l-(+)-tartrate\">\n"
            "\t\t\t\t\t\t\t<CAT text=\"l-(+)-tartrat\">\n"
            "\t\t\t\t\t\t\t\t<CAT text=\"l-(+)-tartra\">\n"
            "\t\t\t\t\t\t\t\t\t<CAT text=\"l-(+)-tartr\">\n"
            "\t\t\t\t\t\t\t\t\t\t<CAT text=\"l-(+)-tart\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"l-(+)-tar\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"l-(+)-ta\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"l-(+)-t\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"l-(+)-\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"l-(+)\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"l-(+\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"l-(\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"l-\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"l\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"-\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"(\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"+\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\")\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"-\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"t\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"a\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"r\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t<CH text=\"t\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t<CH text=\"r\"/>\n"
            "\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t<CH text=\"a\"/>\n"
            "\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t<CH text=\"t\"/>\n"
            "\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t<CH text=\"e\"/>\n"
            "\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t</COMB>\n"
            "\t\t\t\t\t<CAT text=\"l.tartrat\">\n"
            "\t\t\t\t\t\t<CAT text=\"l.tartra\">\n"
            "\t\t\t\t\t\t\t<CAT text=\"l.tartr\">\n"
            "\t\t\t\t\t\t\t\t<CAT text=\"l.tart\">\n"
            "\t\t\t\t\t\t\t\t\t<CAT text=\"l.tar\">\n"
            "\t\t\t\t\t\t\t\t\t\t<CAT text=\"l.ta\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"l.t\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"l.\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"l\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\".\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"t\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t<CH text=\"a\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t<CH text=\"r\"/>\n"
            "\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t<CH text=\"t\"/>\n"
            "\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t<CH text=\"r\"/>\n"
            "\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t<CH text=\"a\"/>\n"
            "\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t<CH text=\"t\"/>\n"
            "\t\t\t\t\t</CAT>\n"
            "\t\t\t\t</COMB>\n"
            "\t\t\t\t<CAT text=\"(l)-ta rtrat\">\n"
            "\t\t\t\t\t<CAT text=\"(l)-ta rtra\">\n"
            "\t\t\t\t\t\t<CAT text=\"(l)-ta rtr\">\n"
            "\t\t\t\t\t\t\t<CAT text=\"(l)-ta rt\">\n"
            "\t\t\t\t\t\t\t\t<CAT text=\"(l)-ta r\">\n"
            "\t\t\t\t\t\t\t\t\t<CAT text=\"(l)-ta \">\n"
            "\t\t\t\t\t\t\t\t\t\t<CAT text=\"(l)-ta\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"(l)-t\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"(l)-\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"(l)\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"(l\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"(\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"l\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\")\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"-\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"t\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t<CH text=\"a\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t<CH text=\" \"/>\n"
            "\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t<CH text=\"r\"/>\n"
            "\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t<CH text=\"t\"/>\n"
            "\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t<CH text=\"r\"/>\n"
            "\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t<CH text=\"a\"/>\n"
            "\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t<CH text=\"t\"/>\n"
            "\t\t\t\t</CAT>\n"
            "\t\t\t</COMB>\n"
            "\t\t\t<CAT text=\"l( +)-tartrat\">\n"
            "\t\t\t\t<CAT text=\"l( +)-tartra\">\n"
            "\t\t\t\t\t<CAT text=\"l( +)-tartr\">\n"
            "\t\t\t\t\t\t<CAT text=\"l( +)-tart\">\n"
            "\t\t\t\t\t\t\t<CAT text=\"l( +)-tar\">\n"
            "\t\t\t\t\t\t\t\t<CAT text=\"l( +)-ta\">\n"
            "\t\t\t\t\t\t\t\t\t<CAT text=\"l( +)-t\">\n"
            "\t\t\t\t\t\t\t\t\t\t<CAT text=\"l( +)-\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"l( +)\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"l( +\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"l( \">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"l(\">\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"l\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"(\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\" \"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"+\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\")\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t\t<CH text=\"-\"/>\n"
            "\t\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t\t<CH text=\"t\"/>\n"
            "\t\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t\t<CH text=\"a\"/>\n"
            "\t\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t\t<CH text=\"r\"/>\n"
            "\t\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t\t<CH text=\"t\"/>\n"
            "\t\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t\t<CH text=\"r\"/>\n"
            "\t\t\t\t\t</CAT>\n"
            "\t\t\t\t\t<CH text=\"a\"/>\n"
            "\t\t\t\t</CAT>\n"
            "\t\t\t\t<CH text=\"t\"/>\n"
            "\t\t\t</CAT>\n"
            "\t\t</COMB>\n"
            "\t</chemical>\n"
            "</chemical>\n";

    CHECK(catalog.prettyPrint() == catalogStr);
}

TEST_CASE("Parse an empty token string") {
    RegexTemplateCatalog catalog;
    catalog.addTokenString("chemical", "");

    const char * catalogStr =
            "<chemical tokenString=\"\">\n"
            "\t<chemical text=\"()\">\n"
            "\t\t<NAN text=\"\"/>\n"
            "\t</chemical>\n"
            "</chemical>\n";

    CHECK(catalog.prettyPrint() == catalogStr);
}

TEST_CASE("Parse several token strings") {
    RegexTemplateCatalog catalog;
    catalog.addTokenString("water", "H20|dihydrogen monoxide|hydroxyl acid");
    catalog.addTokenString("chemical", "l-tartrate|(l*)-tartrate");

    const char * catalogStr =
        "<chemical tokenString=\"l-tartrate|(l*)-tartrate\">\n"
        "\t<chemical text=\"(l-tartrate|(l*)-tartrate)\">\n"
        "\t\t<COMB text=\"l-tartrate|(l*)-tartrate\">\n"
        "\t\t\t<CAT text=\"l-tartrate\">\n"
        "\t\t\t\t<CAT text=\"l-tartrat\">\n"
        "\t\t\t\t\t<CAT text=\"l-tartra\">\n"
        "\t\t\t\t\t\t<CAT text=\"l-tartr\">\n"
        "\t\t\t\t\t\t\t<CAT text=\"l-tart\">\n"
        "\t\t\t\t\t\t\t\t<CAT text=\"l-tar\">\n"
        "\t\t\t\t\t\t\t\t\t<CAT text=\"l-ta\">\n"
        "\t\t\t\t\t\t\t\t\t\t<CAT text=\"l-t\">\n"
        "\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"l-\">\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"l\"/>\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"-\"/>\n"
        "\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t\t\t\t\t\t<CH text=\"t\"/>\n"
        "\t\t\t\t\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t\t\t\t\t<CH text=\"a\"/>\n"
        "\t\t\t\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t\t\t\t<CH text=\"r\"/>\n"
        "\t\t\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t\t\t<CH text=\"t\"/>\n"
        "\t\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t\t<CH text=\"r\"/>\n"
        "\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t<CH text=\"a\"/>\n"
        "\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t<CH text=\"t\"/>\n"
        "\t\t\t\t</CAT>\n"
        "\t\t\t\t<CH text=\"e\"/>\n"
        "\t\t\t</CAT>\n"
        "\t\t\t<CAT text=\"(l*)-tartrate\">\n"
        "\t\t\t\t<CAT text=\"(l*)-tartrat\">\n"
        "\t\t\t\t\t<CAT text=\"(l*)-tartra\">\n"
        "\t\t\t\t\t\t<CAT text=\"(l*)-tartr\">\n"
        "\t\t\t\t\t\t\t<CAT text=\"(l*)-tart\">\n"
        "\t\t\t\t\t\t\t\t<CAT text=\"(l*)-tar\">\n"
        "\t\t\t\t\t\t\t\t\t<CAT text=\"(l*)-ta\">\n"
        "\t\t\t\t\t\t\t\t\t\t<CAT text=\"(l*)-t\">\n"
        "\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"(l*)-\">\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"(l*)\">\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"(l*\">\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"(l\">\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"(\"/>\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"l\"/>\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"*\"/>\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\")\"/>\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"-\"/>\n"
        "\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t\t\t\t\t\t<CH text=\"t\"/>\n"
        "\t\t\t\t\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t\t\t\t\t<CH text=\"a\"/>\n"
        "\t\t\t\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t\t\t\t<CH text=\"r\"/>\n"
        "\t\t\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t\t\t<CH text=\"t\"/>\n"
        "\t\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t\t<CH text=\"r\"/>\n"
        "\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t<CH text=\"a\"/>\n"
        "\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t<CH text=\"t\"/>\n"
        "\t\t\t\t</CAT>\n"
        "\t\t\t\t<CH text=\"e\"/>\n"
        "\t\t\t</CAT>\n"
        "\t\t</COMB>\n"
        "\t</chemical>\n"
        "</chemical>\n"
        "<water tokenString=\"H20|dihydrogen monoxide|hydroxyl acid\">\n"
        "\t<water text=\"(H20|dihydrogen monoxide|hydroxyl acid)\">\n"
        "\t\t<COMB text=\"H20|dihydrogen monoxide|hydroxyl acid\">\n"
        "\t\t\t<COMB text=\"H20|dihydrogen monoxide\">\n"
        "\t\t\t\t<CAT text=\"H20\">\n"
        "\t\t\t\t\t<CAT text=\"H2\">\n"
        "\t\t\t\t\t\t<CH text=\"H\"/>\n"
        "\t\t\t\t\t\t<CH text=\"2\"/>\n"
        "\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t<CH text=\"0\"/>\n"
        "\t\t\t\t</CAT>\n"
        "\t\t\t\t<CAT text=\"dihydrogen monoxide\">\n"
        "\t\t\t\t\t<CAT text=\"dihydrogen monoxid\">\n"
        "\t\t\t\t\t\t<CAT text=\"dihydrogen monoxi\">\n"
        "\t\t\t\t\t\t\t<CAT text=\"dihydrogen monox\">\n"
        "\t\t\t\t\t\t\t\t<CAT text=\"dihydrogen mono\">\n"
        "\t\t\t\t\t\t\t\t\t<CAT text=\"dihydrogen mon\">\n"
        "\t\t\t\t\t\t\t\t\t\t<CAT text=\"dihydrogen mo\">\n"
        "\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"dihydrogen m\">\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"dihydrogen \">\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"dihydrogen\">\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"dihydroge\">\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"dihydrog\">\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"dihydro\">\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"dihydr\">\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"dihyd\">\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"dihy\">\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"dih\">\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"di\">\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"d\"/>\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"i\"/>\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"h\"/>\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"y\"/>\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"d\"/>\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"r\"/>\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"o\"/>\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"g\"/>\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"e\"/>\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"n\"/>\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\" \"/>\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"m\"/>\n"
        "\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t\t\t\t\t\t<CH text=\"o\"/>\n"
        "\t\t\t\t\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t\t\t\t\t<CH text=\"n\"/>\n"
        "\t\t\t\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t\t\t\t<CH text=\"o\"/>\n"
        "\t\t\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t\t\t<CH text=\"x\"/>\n"
        "\t\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t\t<CH text=\"i\"/>\n"
        "\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t<CH text=\"d\"/>\n"
        "\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t<CH text=\"e\"/>\n"
        "\t\t\t\t</CAT>\n"
        "\t\t\t</COMB>\n"
        "\t\t\t<CAT text=\"hydroxyl acid\">\n"
        "\t\t\t\t<CAT text=\"hydroxyl aci\">\n"
        "\t\t\t\t\t<CAT text=\"hydroxyl ac\">\n"
        "\t\t\t\t\t\t<CAT text=\"hydroxyl a\">\n"
        "\t\t\t\t\t\t\t<CAT text=\"hydroxyl \">\n"
        "\t\t\t\t\t\t\t\t<CAT text=\"hydroxyl\">\n"
        "\t\t\t\t\t\t\t\t\t<CAT text=\"hydroxy\">\n"
        "\t\t\t\t\t\t\t\t\t\t<CAT text=\"hydrox\">\n"
        "\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"hydro\">\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"hydr\">\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"hyd\">\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CAT text=\"hy\">\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"h\"/>\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"y\"/>\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"d\"/>\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"r\"/>\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t\t\t\t\t\t\t<CH text=\"o\"/>\n"
        "\t\t\t\t\t\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t\t\t\t\t\t<CH text=\"x\"/>\n"
        "\t\t\t\t\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t\t\t\t\t<CH text=\"y\"/>\n"
        "\t\t\t\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t\t\t\t<CH text=\"l\"/>\n"
        "\t\t\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t\t\t<CH text=\" \"/>\n"
        "\t\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t\t<CH text=\"a\"/>\n"
        "\t\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t\t<CH text=\"c\"/>\n"
        "\t\t\t\t\t</CAT>\n"
        "\t\t\t\t\t<CH text=\"i\"/>\n"
        "\t\t\t\t</CAT>\n"
        "\t\t\t\t<CH text=\"d\"/>\n"
        "\t\t\t</CAT>\n"
        "\t\t</COMB>\n"
        "\t</water>\n"
        "</water>\n";

    CHECK(catalog.prettyPrint() == catalogStr);
}

TEST_CASE("Parse one regex") {
    RegexTemplateCatalog catalog;
    catalog.addRegexTemplate("regex", "1(2|34)*5");

    std::cout << catalog.prettyPrint();

    const char * catalogStr =
            "";

    CHECK(catalog.prettyPrint() == catalogStr);
}

TEST_CASE("Parse an empty regex") {
    RegexTemplateCatalog catalog;
    catalog.addRegexTemplate("regex", "");

    std::cout << catalog.prettyPrint();

    const char * catalogStr =
            "";

    CHECK(catalog.prettyPrint() == catalogStr);
}

TEST_CASE("Parse token strings and regex templates") {
    RegexTemplateCatalog catalog;
    catalog.addTokenString("water", "H20|dihydrogen monoxide|hydroxyl acid");
    catalog.addRegexTemplate("regex", "1(2|34)*5");
    catalog.addRegexTemplate("template", "1(2|3%water%4)*5");

    std::cout << catalog.prettyPrint();

    const char * catalogStr =
            "";

    CHECK(catalog.prettyPrint() == catalogStr);
}

TEST_CASE("Substituting one template") {
    RegexTemplateCatalog catalog;
    catalog.addRegexTemplate("water", "H2O");
    catalog.addRegexTemplate("mater", "CO2%water%CO2");

    std::cout << catalog.prettyPrint();

    const char * catalogStr =
            "";

    CHECK(catalog.prettyPrint() == catalogStr);
}

TEST_CASE("Substituting one token list into one template") {
    RegexTemplateCatalog catalog;
    catalog.addTokenString("water", "H20|dihydrogen monoxide|hydroxyl acid");
    catalog.addRegexTemplate("regex", "1(2|3%water%4)*5");

    std::cout << catalog.prettyPrint();

    const char * catalogStr =
            "";

    CHECK(catalog.prettyPrint() == catalogStr);
}

TEST_CASE("Substituting several templates") {
    RegexTemplateCatalog catalog;
    catalog.addRegexTemplate("oxygen", "O");
    catalog.addRegexTemplate("water", "H2%oxygen%");
    catalog.addRegexTemplate("nitro", "N%oxygen%");
    catalog.addRegexTemplate("mater", "CO2%oxygen%%water%C%oxygen%2");
    catalog.addRegexTemplate("chemical", "%water%%oxygen%");

    std::cout << catalog.prettyPrint();

    const char * catalogStr =
            "";

    CHECK(catalog.prettyPrint() == catalogStr);
}