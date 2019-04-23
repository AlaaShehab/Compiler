//
// Created by alaa on 4/16/2019.
//

#include "NonTerminal.h"

NonTerminal::NonTerminal(string name) {
    NonTerminal::name = name;
    epsilon = false;
}


void NonTerminal::addFirst(string f) {
    first.insert(f);
}

void NonTerminal::addFollow(string f) {
    follow.insert(f);
}

void NonTerminal::addProduction(Production* production) {
    productions.push_back(production);
}

void NonTerminal::addToParsingTable(string terminal, Production * procduction) {
    parsingTable.insert(pair<string, Production*> (terminal, procduction));
}

void NonTerminal::setEpsilon(bool epsilon) {
    NonTerminal::epsilon = epsilon;
}

string NonTerminal::getName() {
    return name;
}

set<string> NonTerminal::getFirstList() {
    return first;
}

set<string> NonTerminal::getFollowList() {
    return follow;
}

map<string, Production*> NonTerminal::getParsingTable() {
    return parsingTable;
}

vector<Production*> NonTerminal::getProductions() {
    return productions;
}

Production* NonTerminal::getTableEntry(string terminal) {
    map<string, Production*>::iterator itr;
    itr = parsingTable.find(terminal);
    if (itr != parsingTable.end()){
        return itr->second;
    }
    return nullptr;
}

bool NonTerminal::isInFirst(string f) {

    return first.find(f) != first.end();
}

bool NonTerminal::isInFollow(string f) {

    return follow.find(f) != follow.end();
}

bool NonTerminal::hasEpsilon() {
    return epsilon;
}

Production* NonTerminal::removePreduction(int index) {
    return cloneProduction(index);
}

Production* NonTerminal::cloneProduction(int index) {
    Production* p = new Production();
    Production* temp = productions[index];
    vector<string> pStrings = temp->getStrings();
    for (int i = 0; i < pStrings.size(); i++) {
        p->addStringToProduction(pStrings[i]);
    }
    productions.erase(productions.begin() + index);
    return p;
}

void NonTerminal::addStringToProductionI(int index, string s) {
    productions[index]->addStringToProduction(s);
}