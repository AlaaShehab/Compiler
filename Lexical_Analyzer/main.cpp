#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <regex>
#include <stack>
#include <set>
#include <map>
#include "Syntax_Analyzer/FirstAndFollowGenerator.h"
#include "Syntax_Analyzer/Production.h"
#include "Syntax_Analyzer/NonTerminal.h"
#include "Syntax_Analyzer/GrammarParser.h"


using namespace std;


void testFirst(){

    NonTerminal* E = new NonTerminal("E");
    NonTerminal* EE = new NonTerminal("EE");
    NonTerminal* T = new NonTerminal("T");
    NonTerminal* TT = new NonTerminal("TT");
    NonTerminal* F = new NonTerminal("F");

    EE->setEpsilon(true);
    TT->setEpsilon(true);

    Production* E1 = new Production();
    E1->addStringToProduction("T");
    E1->addStringToProduction("EE");

    Production* EE1 = new Production();
    EE1->addStringToProduction("+");
    EE1->addStringToProduction("T");
    EE1->addStringToProduction("EE");

    Production* T1 = new Production();
    T1->addStringToProduction("F");
    T1->addStringToProduction("TT");

    Production* TT1 = new Production();
    TT1->addStringToProduction("*");
    TT1->addStringToProduction("F");
    TT1->addStringToProduction("TT");

    Production* F1 = new Production();
    F1->addStringToProduction("(");
    F1->addStringToProduction("E");
    F1->addStringToProduction(")");

    Production* F2 = new Production();
    F2->addStringToProduction("id");

    E->addProduction(E1);
    EE->addProduction(EE1);
    T->addProduction(T1);
    TT->addProduction(TT1);
    F->addProduction(F1);
    F->addProduction(F2);

    set<string> terminals;
    terminals.insert("id");
    terminals.insert("+");
    terminals.insert("*");
    terminals.insert("(");
    terminals.insert(")");

    map<string, NonTerminal*> NonTerminals;
    NonTerminals.insert(pair<string, NonTerminal*> ("E", E));
    NonTerminals.insert(pair<string, NonTerminal*> ("EE", EE));
    NonTerminals.insert(pair<string, NonTerminal*> ("T", T));
    NonTerminals.insert(pair<string, NonTerminal*> ("TT", TT));
    NonTerminals.insert(pair<string, NonTerminal*> ("F", F));

    FirstAndFollowGenerator* p = new FirstAndFollowGenerator(NonTerminals, terminals);
    p->getAllFirst();
    p->getAllFollow();

}

int main() {
    testFirst();

    return 0;
}

