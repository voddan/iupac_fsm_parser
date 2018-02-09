This project's goal is to parse chemical compounds names in IUPAC nomenclature into one of the machine readable formats such as SMILES.

The chosen approach is to reuse major parts of the [OPSIN](https://bitbucket.org/dan2097/opsin/) library since it has the most complete open-source IUPAC grammar description.

This repo is intended to be integrated as a module into [Indigo](https://github.com/epam/Indigo) and thus places a limit on what external libraries can be used.

## The Domain Problem of IUPAC

[IUPAC](https://en.wikipedia.org/wiki/IUPAC_nomenclature_of_organic_chemistry) is a systematic nomenclature of organic chemical compounds. Essentially, it is a widely used set of recommendations on how to name organic molecules in a human-readable form.

While IUPAC makes naming new molecules a relatively straightforward task, the revers problem of constructing a molecular structure from a IUPAC name has not had a satisfactory solution.

Some problems that make parsing an arbitrary IUPAC name difficult:
- One compound may have different IUPAC names
- One IUPAC name may refer to different molecular structures
- IUPAC includes a lot of "dictionary names" for historic compatibility
- IUPAC rules allow slight variations (a.k.a dialects)
- Often IUPAC name omit a part of information if it can be devised from the properties of the atoms


## White Papers & Sources

The ${ROOT}/docs directory contains some relevant white papers about IUPAC parsing collected from the web.

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


## General Plan of Development



## Build

This project is a standard CMake project, so now surprises are here. Note that in order to build tests, you have to clone [googletest](https://github.com/google/googletest.git) into the ${ROOT}/lib directory.

## Libraries

- base_c
  - C-specific implementations that come with Indigo
- base_cpp
  - C++-specific implementations that come with Indigo
- common
  - General helped classes
- tinyxml
  - An XML parser library. Comes with Indigo
- googletest
  - A testing framework by Google. Should be downloaded separately (see the [*Build*](# Build) section)

##