//
// Created by islam on 4/20/19.
//

#include "TableGenerator.h"

using namespace std;

void TableGenerator::prepareAllTables(map<string, NonTerminal*> nonTerminals, set<string> terminals) {
    map<string, NonTerminal *>::iterator it;
    //loops on all nonterminals
    for (it = nonTerminals.begin(); it != nonTerminals.end(); it++) {
        set<string> currentFirst = it->second->getFirstList();
        set<string>::iterator it2;
        //loops on all firsts in the first set
        for (it2 = currentFirst.begin(); it2 != currentFirst.end(); ++it2) {
            vector<Production *> productions = it->second->getProductions();
            //loops on productions
            int targetIndex;
            for (int i = 0; i < productions.size(); i++) {
                //todo replace with bassant's function -- islam
                if (productions[i]->getStringAt(0) == *it2) {
                    targetIndex = i;
                } else {
                    int k = 0;
                    bool start = true;
                    while (nonTerminals.at(productions[i]->getStringAt(0 + k))->hasEpsilon() == true || start == true) {
                        start = false;
                        if (terminals.find(productions[i]->getStringAt(0 + k)) != terminals.end()) {
                            //its terminal and not the wanted string
                            break;
                        } else {
                            //its non-terminal so check the first set of each string in product
                            set<string> temp = nonTerminals.at(productions[i]->getStringAt(0 + k))->getFirstList();
                            if (temp.find(*it2) != temp.end()) {
                                targetIndex = i;
                                break;
                            } else {
                                k++;
                            }
                        }
                    }
                }
            }
            it->second->addToParsingTable(*it2, it->second->getProductions()[targetIndex]);
        }
    }
}