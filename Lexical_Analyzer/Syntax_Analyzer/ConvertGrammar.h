//
// Created by alaa on 4/23/2019.
//

#ifndef LEXICAL_ANALYZER_CONVERTGRAMMAR_H
#define LEXICAL_ANALYZER_CONVERTGRAMMAR_H

#include <string>
#include "vector"
#include "NonTerminal.h"

using namespace std;

class ConvertGrammar {
public:
    ConvertGrammar(map<string, NonTerminal*>, set<string>);
    map<string, NonTerminal*> convert();

private:
    map<string, NonTerminal*> nonTerminals;
    set<string> terminals;

    void leftFactor();
    void removeLeftRecursion();


};


#endif //LEXICAL_ANALYZER_CONVERTGRAMMAR_H
