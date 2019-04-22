//
// Created by akrammoussa on 20/04/19.
//

#ifndef LEXICAL_ANALYZER_FIRSTANDFOLLOWGENERATOR_H
#define LEXICAL_ANALYZER_FIRSTANDFOLLOWGENERATOR_H


#include "NonTerminal.h"
#include "GrammarParser.h"
#include <iostream>
#include <string>
#include <set>

class FirstAndFollowGenerator {
public:

    FirstAndFollowGenerator(map<string, NonTerminal*> nonTerminals, set<string>);

    // functions

    void getAllFirst();
    void getAllFollow();

private:
    set<string> getFollow(NonTerminal*);
    set<string> getFirst(NonTerminal*);

    // variables

    map<string, NonTerminal*> nonTerminals;
    set<string> terminals;
};


#endif //LEXICAL_ANALYZER_FIRSTANDFOLLOWGENERATOR_H
