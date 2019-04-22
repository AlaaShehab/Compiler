//
// Created by akrammoussa on 20/04/19.
//

#include "FirstAndFollowGenerator.h"
#include <iostream>
#include <string>
#include <set>


FirstAndFollowGenerator::FirstAndFollowGenerator(map<string, NonTerminal*> NonTerminals, set<string> Terminals) {
    nonTerminals = NonTerminals;
    terminals = Terminals;
}


void FirstAndFollowGenerator::getAllFirst() {
    map<string, NonTerminal*>::iterator it;
    for ( it = nonTerminals.begin(); it != nonTerminals.end(); it++ ) {
        getFirst(it->second);
    }
}

set<string> FirstAndFollowGenerator::getFirst(NonTerminal * nonTerminal) {
    if (nonTerminal->getFirstList().size() != 0) { return nonTerminal->getFirstList();}
    vector<Production*> productions = nonTerminal->getProductions();
    for (int i = 0; i < productions.size(); i++) {
        vector<string> strings = productions[i]->getStrings();
        for (int j = 0; j < strings.size(); ++j) {
            if(terminals.find(strings[j]) != terminals.end()) {
                nonTerminal->addFirst(strings[j]);
                break;
            } else {
                set<string> temp = getFirst(nonTerminals.at(strings[j]));
                for (auto elem : temp) {
                    nonTerminal->addFirst(elem);
                }
                if (!nonTerminals.at(strings[j])->hasEpsilon()) {
                    break;
                }
            }
        }
    }
    return nonTerminal->getFirstList();
}

void FirstAndFollowGenerator::getAllFollow() {
    //nonTerminals[0]->addFollow("$");
    map<string, NonTerminal*>::iterator it;
    it = nonTerminals.begin();
    it->second->addFollow("$");
    for ( it = nonTerminals.begin(); it != nonTerminals.end(); it++ ) {
        if( it == nonTerminals.begin() || it->second->getFollowList().size()==0 ) {
            getFollow(it->second);
        }
    }
}


set<string> FirstAndFollowGenerator::getFollow(NonTerminal * nonTerminal) {

    if (nonTerminal->getFollowList().size()!=0 && !(nonTerminal->getFollowList().size() == 1 && nonTerminal->getFollowList().find("$") != nonTerminal->getFollowList().end())){
        return nonTerminal->getFollowList();
    }
    map<string, NonTerminal*>:: iterator it;
    for (it =nonTerminals.begin(); it !=nonTerminals.end(); it++) {
        vector<Production*> productions = it->second->getProductions();
        for (int i = 0; i < productions.size() ; ++i) {
            int index = productions[i]->contains(nonTerminal->getName());
            if  (index!=-1){
                if (index == productions[i]->getStrings().size()-1){
                    set<string> tempFollow = getFollow(it->second);
                    for (auto elem : tempFollow) {
                        nonTerminal->addFollow(elem);
                    }
                } else{
                    while (index != productions[i]->getStrings().size()-1){
                        index++;
                        if(terminals.find((productions[i]->getStringAt(index))) != terminals.end()){
                            nonTerminal->addFollow(productions[i]->getStringAt(index));
                            break;
                        }
                        else{
                            set<string> tempFollow = nonTerminals.at(productions[i]->getStringAt(index))->getFirstList();
                            for (auto elem : tempFollow) {
                                nonTerminal->addFollow(elem);
                            }
                            if (!nonTerminals.at(productions[i]->getStringAt(index))->hasEpsilon()){
                                break;
                            }
                        }
                        if (index == productions[i]->getStrings().size()-1){
                            set<string> tempFollow = getFollow(it->second);
                            for (auto elem : tempFollow) {
                                nonTerminal->addFollow(elem);
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
    return nonTerminal->getFollowList();
}