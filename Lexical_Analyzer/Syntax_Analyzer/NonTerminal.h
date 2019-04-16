//
// Created by alaa on 4/16/2019.
//

#ifndef LEXICAL_ANALYZER_NONTERMINAL_H
#define LEXICAL_ANALYZER_NONTERMINAL_H

#include <string>
#include <set>
#include <map>
#include "vector"
#include "Production.h"

using namespace std;

class NonTerminal {

public:
    /*
     * Constructor
     */
    NonTerminal (string);

    string getName();
    /*
     * Getters and setters
     */
    map<string, Production*> getParsingTable();
    set<string> getFirst();
    set<string> getFollow();
    vector<Production> getProductions();

    void addFirst(string);
    void addFollow(string);
    void addProduction(Production);
    void addToParsingTable(string, Production*);

    /*
     * Helping methods
     */
    bool isInFirst(string);
    bool isInFollow(string);
    Production* getTableEntry(string);


private:
    map<string, Production*> parsingTable;
    set<string> first;
    set<string> follow;
    vector<Production> productions;

    string name;

};


#endif //LEXICAL_ANALYZER_NONTERMINAL_H
