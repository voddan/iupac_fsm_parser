This project's goal is to parse chemical compounds names in IUPAC nomenclature into one of the machine readable formats such as SMILES.

The chosen approach is to reuse major parts of the [OPSIN](https://bitbucket.org/dan2097/opsin/) library since it has the most complete open-source IUPAC grammar description.

This repo is intended to be integrated as a module into [Indigo](https://github.com/epam/Indigo) and thus places a limit on what external libraries can be used.

## The Domain Problem of IUPAC

[IUPAC](https://en.wikipedia.org/wiki/IUPAC_nomenclature_of_organic_chemistry) is a systematic nomenclature of organic chemical compounds. Essentially, it is a widely used set of recommendations on how to name organic molecules in a human-readable form.

While IUPAC makes naming new molecules a relatively straightforward task, the reverse problem of constructing a molecular structure from a IUPAC name has not had a satisfactory solution.

Some problems that make parsing an arbitrary IUPAC name difficult:
- One compound may have different IUPAC names
- One IUPAC name may refer to different molecular structures
- IUPAC includes a lot of "dictionary names" for historic compatibility
- IUPAC rules allow slight variations (a.k.a dialects)
- Often IUPAC name omits a part of information if it can be devised from the properties of the atoms


## White Papers & Sources

The [${ROOT}/docs](docs/.) directory contains some relevant white papers about IUPAC parsing collected from the web:

- [Brecher, 1999, "Name=Struct, A Practical Approach"](docs/Brecher-1999-Name=Struct_A Practical_Approach.pdf)

  - A high-level description of the ChemDraw parser

- [CookeFox, 1989, "Computer translation of IUPAC"](docs/CookeFox-1989-Computer_translation_of_IUPAC.pdf)

  - A detailed explanation of grammar-based IUPAC parsing in 5 parts + an example formal IUPAC grammar

- [Kirby, 1991, "Semiautomatic Name Correction"](docs/Kirby-1991-Semiautomatic Name Correction.pdf)

  - An approach to parsing IUPAC names with errors

- [Lowe, 2011, "OPSIN, an Open Source Solution"](docs/Lowe-2011-OPSIN an Open Source Solution.pdf)

  - High-level description of the OPSIN library

- [Lowe, 2012, "Extraction of Chemical Structures"](docs/Lowe-2012-Extraction-of-Chemical-Structures.pdf)

  - The most detailed description of the OPSIN library
  
- [Serebrykov, 2006, "Theory and realisation of programming languages"](http://www.ccas.ru/depart/MMSP/furugyan/doc/_TRYAPBOOK_pdf.pdf)

  - A book on building efficient parsers (in Russian)
  
  - Original title: "Теория и реализация языков программирования; Сереьряков В.А. и др.; Москва, МЗ Пресс, 2006"
  
  - Chapter 3.3.3 "Constructing FSM from RegEx" should be of an immediate use


## General Plan of Development

Indigo already has a rudimental IUPAC parser which is able to parse dictionary compound names, carbon chains and some other structures. The biggest flaw of the current system is its lack of systematisation and extensibility, which makes it hard to correcting the parsing algorithm or add something new to it.

On the other hand, the OPSIN parser uses a set of XML configuration files which describe a large portion of the IUPAC grammar. Since OPSIN has an MIT license, we are able to copy those configuration into our project. Those configs are places in the [${ROOT}/grammar](grammar/.) directory.

In order to take advantage of the Indigo existing infrastructure and OPSIN grammar we plan to integrate into the syntax-analizing faze of the Indigo IUPAC parser (classes in `molecule/molecule_name_parser`). 

That symbiosis of the two parsers would work in the following steps:

- On start up
  - Parse XML files from [${ROOT}/grammar](grammar/.) into a syntax tree
  - Build a DFA (Deterministic Finite Automata) from the syntax tree
- On an invocation
  - Run the DFA on the input string and generate a syntax tree of the molecule name
  - Transform the molecule syntax tree into a build tree of the molecule structure
  - Generate SMILES from the molecule build tree 
  
Parsing the XML configs can be handled with the `tinyxml` library. However, the RegEx expressions that are contained in the configs have to be hand-parsed in order for us to have access to their syntactic structure. A good way to accomplish that is to implement a DFA to parse the RegEx and to build the DFA for IUPAC.

## Build

This project is a standard CMake project, so now surprises are here. Note that in order to build tests, you have to clone [googletest](https://github.com/google/googletest.git) into the [${ROOT}/lib](lib/.) directory.

## Libraries

- base_c
  - C-specific implementations that come with Indigo
- base_cpp
  - C++-specific implementations that come with Indigo
- common
  - General helper classes
- tinyxml
  - An XML parser library. Comes with Indigo
- googletest
  - A testing framework by Google. Should be downloaded separately (see the [Build](README.md#build) section)

## Modules and Classes

Here is a brief overview of main modules and class of the current implementation:

### regular-fsm

Module contains a Finite State Machine (a.k.a. FSA) to represent a regular grammar. Should be used to parse the XML configs and compile a FSA to parse IUPAC syntax into a syntax tree.

`SyntaxTree` - an abstract syntax tree consisting of nodes `SyntaxTreeNode` 
`RegexSyntaxTree` - an implementation of `SyntaxTree` consisting of nodes `RegexSyntaxTreeNode` 

`RegexTemplaitCatalog` - a template engine which can assemble parsed trees `RegexSyntaxTree` into one syntax tree without template markers

`StateMachine` - a FSA which can parse a `string` into a `SyntaxTree`. Can be build from a`RegexSyntaxTree`

`TextPosition` - a helper struct to encapsulate a text position in the input text (and possibly provide a hepful error message if the syntax is incorrect) 