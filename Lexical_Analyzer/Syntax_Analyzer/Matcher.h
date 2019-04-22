//
// Created by akrammoussa on 22/04/19.
//

#ifndef LEXICAL_ANALYZER_MATCHER_H
#define LEXICAL_ANALYZER_MATCHER_H

#include "NonTerminal.h"
#include "GrammarParser.h"
#include <iostream>
#include <string>
#include <set>
#include <stack>
#include "../Lexical/Token.h"


class Matcher {
public:
    Matcher(map<string, NonTerminal*> nonTerminals, set<string>,string firstName,vector<Token*> tokens);
    void Match();

private:
    // variables

    map<string, NonTerminal*> nonTerminals;
    set<string> terminals;
    string firstName;
    vector<Token*> tokens;
    vector<string> outputs;


    void outputProduction(vector<string> vector);

    void writeTheOutput();
};


#endif //LEXICAL_ANALYZER_MATCHER_H
