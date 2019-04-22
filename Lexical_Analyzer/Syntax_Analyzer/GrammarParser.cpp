//
// Created by alaa on 4/16/2019.
//

#include "GrammarParser.h"
#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <set>
#include <map>

using namespace std;

void GrammarParser::readFile(string fileName) {
    string line;
    string temp;
    ifstream grammarFile(fileName);
    if (grammarFile.is_open())
    {
        while (getline(grammarFile,line))
        {
            if (line[line.find_first_not_of(' ')] == '#') {
                if (temp != "") {
                    grammarRules.push_back(temp);
                }
                temp = line;
                continue;
            }
            temp.append(" ").append(line);
        }
        grammarRules.push_back(temp);
        grammarFile.close();
    } else {
        cout << "file cannot be opened" << endl;
    }
    firstProductionSet = true;
}

void GrammarParser::parseGrammar() {
    /*
     * TODO write assumption that rules
     * TODO are parsed as follows NonT = production
     */
    for (int i = 0; i < grammarRules.size(); i++) {
        parseProduction(grammarRules[i]);
    }
}

//TODO what are types of reserved symbols ask mo3ida
void GrammarParser::parseProduction(string production) {

    string NonTerminalName = extractName(production);
    NonTerminal* nonTerminal = new NonTerminal(NonTerminalName);

    int startOfProd = production.find_first_of('=');
    production = production.substr(startOfProd + 1, production.size() - startOfProd);

    string temp;
    bool terminal = false;
    Production* p = new Production();
    //TODO didn't handle a single quote or | as terminal
    for (int i = 0; i < production.size(); i++) {
        if (production[i] == ' ') {
            if (!temp.empty()) {
                p->addStringToProduction(temp);
                if (terminal) {
                    terminals.insert(temp);
                }
            }
            terminal = false;
            temp = "";
        } else if (production[i] == '|') {
            //TODO add assumptions | must have a space before it
            nonTerminal->addProduction(p);
            temp = "";
            terminal = false;
            p = new Production();
        } else if (production[i] == '\'') {
            terminal = true;
        } else if (production[i] == 'L' && production[i-1] == '\\') {
            nonTerminal->setEpsilon(true);
            temp = "";
            terminal = false;
        } else {
            temp += production[i];
        }
    }
    if (!temp.empty()) {
        p->addStringToProduction(temp);
        nonTerminal->addProduction(p);
    }
    if (terminal) {
        terminals.insert(temp);
    }
    nonTerminals.insert(pair<string, NonTerminal*> (NonTerminalName, nonTerminal));

    if (firstProductionSet) {
        firstNonTerminal = nonTerminal;
        firstProductionSet = false;
    }


}

string GrammarParser::extractName(string production) {
    regex rgx("\\w+");
    smatch match;
    const string input = production;
    regex_search(input.begin(), input.end(), match, rgx);

    return match.str(0);
}

map<string, NonTerminal*> GrammarParser::getNonTerminals() {
    return nonTerminals;
}

set<string> GrammarParser::getTerminals() {
    return terminals;
}

NonTerminal* GrammarParser::getfirstNonTerminal() {
    return firstNonTerminal;
}