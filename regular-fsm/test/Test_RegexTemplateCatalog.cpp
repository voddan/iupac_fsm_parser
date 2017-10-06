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
            "%chemical% : H2O\n"
            "\t<%chemical%: (H2O)>\n"
            "\t\t<.: H2O>\n"
            "\t\t\t<.: H2>\n"
            "\t\t\t\t<char: H>\n"
            "\t\t\t\t<char: 2>\n"
            "\t\t\t</.>\n"
            "\t\t\t<char: O>\n"
            "\t\t</.>\n"
            "\t</%chemical%>\n";

    CHECK(catalog.prettyPrint() == catalogStr);
}

TEST_CASE("Parse one token string, multiple tokens") {
    RegexTemplateCatalog catalog;
    catalog.addTokenString("chemical", "l-tartrate|(l*)-tartrate|l(+?)-tartrate|l-(+)-tartrate|l.tartrat|(l)-ta rtrat|l( +)-tartrat");

    const char * catalogStr =
            "%chemical% : l-tartrate|(l*)-tartrate|l(+?)-tartrate|l-(+)-tartrate|l.tartrat|(l)-ta rtrat|l( +)-tartrat\n"
            "\t<%chemical%: (l-tartrate|(l*)-tartrate|l(+?)-tartrate|l-(+)-tartrate|l.tartrat|(l)-ta rtrat|l( +)-tartrat)>\n"
            "\t\t<|: l-tartrate|(l*)-tartrate|l(+?)-tartrate|l-(+)-tartrate|l.tartrat|(l)-ta rtrat|l( +)-tartrat>\n"
            "\t\t\t<|: l-tartrate|(l*)-tartrate|l(+?)-tartrate|l-(+)-tartrate|l.tartrat|(l)-ta rtrat>\n"
            "\t\t\t\t<|: l-tartrate|(l*)-tartrate|l(+?)-tartrate|l-(+)-tartrate|l.tartrat>\n"
            "\t\t\t\t\t<|: l-tartrate|(l*)-tartrate|l(+?)-tartrate|l-(+)-tartrate>\n"
            "\t\t\t\t\t\t<|: l-tartrate|(l*)-tartrate|l(+?)-tartrate>\n"
            "\t\t\t\t\t\t\t<|: l-tartrate|(l*)-tartrate>\n"
            "\t\t\t\t\t\t\t\t<.: l-tartrate>\n"
            "\t\t\t\t\t\t\t\t\t<.: l-tartrat>\n"
            "\t\t\t\t\t\t\t\t\t\t<.: l-tartra>\n"
            "\t\t\t\t\t\t\t\t\t\t\t<.: l-tartr>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t<.: l-tart>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t<.: l-tar>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t<.: l-ta>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<.: l-t>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<.: l->\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: l>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: ->\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: t>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: a>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: r>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t<char: t>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t<char: r>\n"
            "\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t<char: a>\n"
            "\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t<char: t>\n"
            "\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t<char: e>\n"
            "\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t<.: (l*)-tartrate>\n"
            "\t\t\t\t\t\t\t\t\t<.: (l*)-tartrat>\n"
            "\t\t\t\t\t\t\t\t\t\t<.: (l*)-tartra>\n"
            "\t\t\t\t\t\t\t\t\t\t\t<.: (l*)-tartr>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t<.: (l*)-tart>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t<.: (l*)-tar>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t<.: (l*)-ta>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<.: (l*)-t>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<.: (l*)->\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<.: (l*)>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<.: (l*>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<.: (l>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: (>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: l>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: *>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: )>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: ->\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: t>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: a>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: r>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t<char: t>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t<char: r>\n"
            "\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t<char: a>\n"
            "\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t<char: t>\n"
            "\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t<char: e>\n"
            "\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t</|>\n"
            "\t\t\t\t\t\t\t<.: l(+?)-tartrate>\n"
            "\t\t\t\t\t\t\t\t<.: l(+?)-tartrat>\n"
            "\t\t\t\t\t\t\t\t\t<.: l(+?)-tartra>\n"
            "\t\t\t\t\t\t\t\t\t\t<.: l(+?)-tartr>\n"
            "\t\t\t\t\t\t\t\t\t\t\t<.: l(+?)-tart>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t<.: l(+?)-tar>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t<.: l(+?)-ta>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t<.: l(+?)-t>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<.: l(+?)->\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<.: l(+?)>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<.: l(+?>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<.: l(+>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<.: l(>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: l>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: (>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: +>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: ?>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: )>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: ->\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: t>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: a>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t<char: r>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t<char: t>\n"
            "\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t<char: r>\n"
            "\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t<char: a>\n"
            "\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t<char: t>\n"
            "\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t<char: e>\n"
            "\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t</|>\n"
            "\t\t\t\t\t\t<.: l-(+)-tartrate>\n"
            "\t\t\t\t\t\t\t<.: l-(+)-tartrat>\n"
            "\t\t\t\t\t\t\t\t<.: l-(+)-tartra>\n"
            "\t\t\t\t\t\t\t\t\t<.: l-(+)-tartr>\n"
            "\t\t\t\t\t\t\t\t\t\t<.: l-(+)-tart>\n"
            "\t\t\t\t\t\t\t\t\t\t\t<.: l-(+)-tar>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t<.: l-(+)-ta>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t<.: l-(+)-t>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t<.: l-(+)->\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<.: l-(+)>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<.: l-(+>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<.: l-(>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<.: l->\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: l>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: ->\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: (>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: +>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: )>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: ->\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: t>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t<char: a>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t<char: r>\n"
            "\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t<char: t>\n"
            "\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t<char: r>\n"
            "\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t<char: a>\n"
            "\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t<char: t>\n"
            "\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t<char: e>\n"
            "\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t</|>\n"
            "\t\t\t\t\t<.: l.tartrat>\n"
            "\t\t\t\t\t\t<.: l.tartra>\n"
            "\t\t\t\t\t\t\t<.: l.tartr>\n"
            "\t\t\t\t\t\t\t\t<.: l.tart>\n"
            "\t\t\t\t\t\t\t\t\t<.: l.tar>\n"
            "\t\t\t\t\t\t\t\t\t\t<.: l.ta>\n"
            "\t\t\t\t\t\t\t\t\t\t\t<.: l.t>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t<.: l.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t<char: l>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t<char: .>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t<char: t>\n"
            "\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t<char: a>\n"
            "\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t<char: r>\n"
            "\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t<char: t>\n"
            "\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t<char: r>\n"
            "\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t<char: a>\n"
            "\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t<char: t>\n"
            "\t\t\t\t\t</.>\n"
            "\t\t\t\t</|>\n"
            "\t\t\t\t<.: (l)-ta rtrat>\n"
            "\t\t\t\t\t<.: (l)-ta rtra>\n"
            "\t\t\t\t\t\t<.: (l)-ta rtr>\n"
            "\t\t\t\t\t\t\t<.: (l)-ta rt>\n"
            "\t\t\t\t\t\t\t\t<.: (l)-ta r>\n"
            "\t\t\t\t\t\t\t\t\t<.: (l)-ta >\n"
            "\t\t\t\t\t\t\t\t\t\t<.: (l)-ta>\n"
            "\t\t\t\t\t\t\t\t\t\t\t<.: (l)-t>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t<.: (l)->\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t<.: (l)>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t<.: (l>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: (>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: l>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: )>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t<char: ->\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t<char: t>\n"
            "\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t<char: a>\n"
            "\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t<char:  >\n"
            "\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t<char: r>\n"
            "\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t<char: t>\n"
            "\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t<char: r>\n"
            "\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t<char: a>\n"
            "\t\t\t\t\t</.>\n"
            "\t\t\t\t\t<char: t>\n"
            "\t\t\t\t</.>\n"
            "\t\t\t</|>\n"
            "\t\t\t<.: l( +)-tartrat>\n"
            "\t\t\t\t<.: l( +)-tartra>\n"
            "\t\t\t\t\t<.: l( +)-tartr>\n"
            "\t\t\t\t\t\t<.: l( +)-tart>\n"
            "\t\t\t\t\t\t\t<.: l( +)-tar>\n"
            "\t\t\t\t\t\t\t\t<.: l( +)-ta>\n"
            "\t\t\t\t\t\t\t\t\t<.: l( +)-t>\n"
            "\t\t\t\t\t\t\t\t\t\t<.: l( +)->\n"
            "\t\t\t\t\t\t\t\t\t\t\t<.: l( +)>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t<.: l( +>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t<.: l( >\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t<.: l(>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: l>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: (>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char:  >\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t<char: +>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t<char: )>\n"
            "\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t<char: ->\n"
            "\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t<char: t>\n"
            "\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t<char: a>\n"
            "\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t<char: r>\n"
            "\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t<char: t>\n"
            "\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t<char: r>\n"
            "\t\t\t\t\t</.>\n"
            "\t\t\t\t\t<char: a>\n"
            "\t\t\t\t</.>\n"
            "\t\t\t\t<char: t>\n"
            "\t\t\t</.>\n"
            "\t\t</|>\n"
            "\t</%chemical%>\n";

    CHECK(catalog.prettyPrint() == catalogStr);
}

TEST_CASE("Parse an empty token string") {
    RegexTemplateCatalog catalog;
    catalog.addTokenString("chemical", "");

    const char * catalogStr =
            "%chemical% : \n"
            "\t<%chemical%: ()>\n"
            "\t\t<NaN: >\n"
            "\t</%chemical%>\n";

    CHECK(catalog.prettyPrint() == catalogStr);
}

TEST_CASE("Parse several token strings") {
    RegexTemplateCatalog catalog;
    catalog.addTokenString("water", "H20|dihydrogen monoxide|hydroxyl acid");
    catalog.addTokenString("chemical", "l-tartrate|(l*)-tartrate");

    const char * catalogStr =
            "%chemical% : l-tartrate|(l*)-tartrate\n"
            "\t<%chemical%: (l-tartrate|(l*)-tartrate)>\n"
            "\t\t<|: l-tartrate|(l*)-tartrate>\n"
            "\t\t\t<.: l-tartrate>\n"
            "\t\t\t\t<.: l-tartrat>\n"
            "\t\t\t\t\t<.: l-tartra>\n"
            "\t\t\t\t\t\t<.: l-tartr>\n"
            "\t\t\t\t\t\t\t<.: l-tart>\n"
            "\t\t\t\t\t\t\t\t<.: l-tar>\n"
            "\t\t\t\t\t\t\t\t\t<.: l-ta>\n"
            "\t\t\t\t\t\t\t\t\t\t<.: l-t>\n"
            "\t\t\t\t\t\t\t\t\t\t\t<.: l->\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t<char: l>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t<char: ->\n"
            "\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t<char: t>\n"
            "\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t<char: a>\n"
            "\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t<char: r>\n"
            "\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t<char: t>\n"
            "\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t<char: r>\n"
            "\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t<char: a>\n"
            "\t\t\t\t\t</.>\n"
            "\t\t\t\t\t<char: t>\n"
            "\t\t\t\t</.>\n"
            "\t\t\t\t<char: e>\n"
            "\t\t\t</.>\n"
            "\t\t\t<.: (l*)-tartrate>\n"
            "\t\t\t\t<.: (l*)-tartrat>\n"
            "\t\t\t\t\t<.: (l*)-tartra>\n"
            "\t\t\t\t\t\t<.: (l*)-tartr>\n"
            "\t\t\t\t\t\t\t<.: (l*)-tart>\n"
            "\t\t\t\t\t\t\t\t<.: (l*)-tar>\n"
            "\t\t\t\t\t\t\t\t\t<.: (l*)-ta>\n"
            "\t\t\t\t\t\t\t\t\t\t<.: (l*)-t>\n"
            "\t\t\t\t\t\t\t\t\t\t\t<.: (l*)->\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t<.: (l*)>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t<.: (l*>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t<.: (l>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: (>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: l>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: *>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t<char: )>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t<char: ->\n"
            "\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t<char: t>\n"
            "\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t<char: a>\n"
            "\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t<char: r>\n"
            "\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t<char: t>\n"
            "\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t<char: r>\n"
            "\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t<char: a>\n"
            "\t\t\t\t\t</.>\n"
            "\t\t\t\t\t<char: t>\n"
            "\t\t\t\t</.>\n"
            "\t\t\t\t<char: e>\n"
            "\t\t\t</.>\n"
            "\t\t</|>\n"
            "\t</%chemical%>\n"
            "%water% : H20|dihydrogen monoxide|hydroxyl acid\n"
            "\t<%water%: (H20|dihydrogen monoxide|hydroxyl acid)>\n"
            "\t\t<|: H20|dihydrogen monoxide|hydroxyl acid>\n"
            "\t\t\t<|: H20|dihydrogen monoxide>\n"
            "\t\t\t\t<.: H20>\n"
            "\t\t\t\t\t<.: H2>\n"
            "\t\t\t\t\t\t<char: H>\n"
            "\t\t\t\t\t\t<char: 2>\n"
            "\t\t\t\t\t</.>\n"
            "\t\t\t\t\t<char: 0>\n"
            "\t\t\t\t</.>\n"
            "\t\t\t\t<.: dihydrogen monoxide>\n"
            "\t\t\t\t\t<.: dihydrogen monoxid>\n"
            "\t\t\t\t\t\t<.: dihydrogen monoxi>\n"
            "\t\t\t\t\t\t\t<.: dihydrogen monox>\n"
            "\t\t\t\t\t\t\t\t<.: dihydrogen mono>\n"
            "\t\t\t\t\t\t\t\t\t<.: dihydrogen mon>\n"
            "\t\t\t\t\t\t\t\t\t\t<.: dihydrogen mo>\n"
            "\t\t\t\t\t\t\t\t\t\t\t<.: dihydrogen m>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t<.: dihydrogen >\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t<.: dihydrogen>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t<.: dihydroge>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<.: dihydrog>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<.: dihydro>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<.: dihydr>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<.: dihyd>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<.: dihy>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<.: dih>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<.: di>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: d>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: i>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: h>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: y>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: d>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: r>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: o>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: g>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: e>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: n>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t<char:  >\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t<char: m>\n"
            "\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t<char: o>\n"
            "\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t<char: n>\n"
            "\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t<char: o>\n"
            "\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t<char: x>\n"
            "\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t<char: i>\n"
            "\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t<char: d>\n"
            "\t\t\t\t\t</.>\n"
            "\t\t\t\t\t<char: e>\n"
            "\t\t\t\t</.>\n"
            "\t\t\t</|>\n"
            "\t\t\t<.: hydroxyl acid>\n"
            "\t\t\t\t<.: hydroxyl aci>\n"
            "\t\t\t\t\t<.: hydroxyl ac>\n"
            "\t\t\t\t\t\t<.: hydroxyl a>\n"
            "\t\t\t\t\t\t\t<.: hydroxyl >\n"
            "\t\t\t\t\t\t\t\t<.: hydroxyl>\n"
            "\t\t\t\t\t\t\t\t\t<.: hydroxy>\n"
            "\t\t\t\t\t\t\t\t\t\t<.: hydrox>\n"
            "\t\t\t\t\t\t\t\t\t\t\t<.: hydro>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t<.: hydr>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t<.: hyd>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t<.: hy>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: h>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: y>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t\t<char: d>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t\t<char: r>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t\t<char: o>\n"
            "\t\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t\t<char: x>\n"
            "\t\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t\t<char: y>\n"
            "\t\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t\t<char: l>\n"
            "\t\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t\t<char:  >\n"
            "\t\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t\t<char: a>\n"
            "\t\t\t\t\t\t</.>\n"
            "\t\t\t\t\t\t<char: c>\n"
            "\t\t\t\t\t</.>\n"
            "\t\t\t\t\t<char: i>\n"
            "\t\t\t\t</.>\n"
            "\t\t\t\t<char: d>\n"
            "\t\t\t</.>\n"
            "\t\t</|>\n"
            "\t</%water%>\n";

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