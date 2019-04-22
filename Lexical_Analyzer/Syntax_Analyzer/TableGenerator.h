//
// Created by islam on 4/20/19.
//

#ifndef LEXICAL_ANALYZER_TABLEGENERATOR_H
#define LEXICAL_ANALYZER_TABLEGENERATOR_H
#include <map>
#include "NonTerminal.h"
#include <string>
#include <iostream>
#include <set>


class TableGenerator {
public:
    void prepareAllTables(map<string, NonTerminal*>, set<string>);
};


#endif //LEXICAL_ANALYZER_TABLEGENERATOR_H
