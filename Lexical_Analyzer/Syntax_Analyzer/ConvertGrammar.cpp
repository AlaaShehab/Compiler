//
// Created by alaa on 4/23/2019.
//

#include "ConvertGrammar.h"
#include <string>
#include "vector"
#include "Production.h"
#include "NonTerminal.h"
#include <map>

using namespace std;

ConvertGrammar::ConvertGrammar(map<string, NonTerminal *> nonTerminals, set<string> terminals) {
    ConvertGrammar::nonTerminals = nonTerminals;
    ConvertGrammar::terminals = terminals;
}

map<string, NonTerminal*> ConvertGrammar::convert() {
   leftFactor();
   removeLeftRecursion();
   return nonTerminals;
}

//TODO condition of break is wrong
void ConvertGrammar::leftFactor() {
    map<string, NonTerminal *>::iterator itr;
    for (itr = nonTerminals.begin(); itr != nonTerminals.end(); itr++) {
        vector<Production*> productions = itr->second->getProductions();
        //just for debug
        NonTerminal* nonT = itr->second;
        bool nochange = false;
        int loop = productions.size();
        while (!nochange && !productions.empty()) {
            vector<Production*> temp;
            temp.push_back(itr->second->removePreduction(0));
            productions = itr->second->getProductions();
            for (int i = 0; i < itr->second->getProductions().size(); i++) {
                if (productions[i]->getStringAt(0) == temp[0]->getStringAt(0)) {
                    temp.push_back(itr->second->removePreduction(i));
                    productions = itr->second->getProductions();
                }
            }
            string newNonTerminalName = temp[0]->getStringAt(0) + "1";
            if (temp.size() != 1) {
                Production* p = new Production();
                p->addStringToProduction(temp[0]->getStringAt(0));
                p->addStringToProduction(newNonTerminalName);
                itr->second->addProduction(p);

                NonTerminal* n = new NonTerminal(newNonTerminalName);
                for (int j = 0; j < temp.size(); j++) {
                    vector<string> s = temp[j]->getStrings();
                    if (s.size() == 1) {
                        n->setEpsilon(true);
                        continue;
                    }
                    Production* p1 = new Production();
                    for (int k = 1; k < s.size(); k++) {
                        p1->addStringToProduction(s[k]);
                    }
                    n->addProduction(p1);
                }

                nonTerminals.insert(pair<string, NonTerminal*>(newNonTerminalName, n));

            } else {
                itr->second->addProduction(temp[0]);
            }

            loop--;
            if (loop == 0) {
                nochange = true;
            }
            productions = itr->second->getProductions();
        }
    }
}

void ConvertGrammar::removeLeftRecursion() {
    map<string, NonTerminal *>::iterator itr;
    for (itr = nonTerminals.begin(); itr != nonTerminals.end(); itr++) {

        vector<Production*> productions = itr->second->getProductions();
        for (int i = 0; i < productions.size(); i++) {

            if (itr->first == productions[i]->getStringAt(0)) {
                string newNonTerminalName = itr->first + "2";
                Production* p = itr->second->removePreduction(i);
                productions = itr->second->getProductions();
                for (int j = 0; j < productions.size(); j++) {
                    itr->second->addStringToProductionI(j, newNonTerminalName);
                }
                NonTerminal* n = new NonTerminal(newNonTerminalName);
                n->setEpsilon(true);
                Production* p1 = new Production();
                for (int k = 1; k < p->getStrings().size(); k++) {
                    p1->addStringToProduction(p->getStringAt(k));
                }
                p1->addStringToProduction(newNonTerminalName);
                n->addProduction(p1);
                nonTerminals.insert(pair<string, NonTerminal*>(newNonTerminalName, n));
                break;
            }
        }
    }

}