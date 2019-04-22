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
    void readFile(string);
    void parseGrammar();
    set<string> getTerminals();
    map<string, NonTerminal*> getNonTerminals();
    //return first production
    NonTerminal* getfirstNonTerminal();

private:
    set<string> terminals;
    map<string, NonTerminal*> nonTerminals;

    vector<string> grammarRules;

    void parseProduction(string);
    string extractName(string);

    //first production
    NonTerminal* firstNonTerminal;
    bool firstProductionSet;


};


#endif //LEXICAL_ANALYZER_GRAMMARPARSER_H
