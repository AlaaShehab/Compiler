//
// Created by alaa on 4/16/2019.
//

#ifndef LEXICAL_ANALYZER_GRAMMARPARSER_H
#define LEXICAL_ANALYZER_GRAMMARPARSER_H

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <regex>
#include <set>
#include <map>
#include "NonTerminal.h"


using namespace std;

class GrammarParser {
public :
    set<string> getTerminals();
    map<string, NonTerminal*> getNonTerminals();

};


#endif //LEXICAL_ANALYZER_GRAMMARPARSER_H
