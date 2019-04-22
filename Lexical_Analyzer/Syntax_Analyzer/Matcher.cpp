//
// Created by akrammoussa on 22/04/19.
//

#include "Matcher.h"

Matcher::Matcher(map<string, NonTerminal *> nonTerminals, set<string> terminals ,string firstName,vector<Token*> tokens) {
    this->nonTerminals = nonTerminals;
    this->terminals = terminals;
    this->firstName = firstName;
    this->tokens = tokens;
}

void Matcher::Match() {
    stack<string> matching;
    matching.push("$");
    matching.push(firstName);
    Token* token = new Token("$","");
    tokens.push_back(token);
    for (int i = 0; i < tokens.size(); ++i) {
        if (tokens[i]->getTokenType() == "$"){
            if (matching.top() == "$"){
                outputs.push_back("accept");
            } else{
                outputs.push_back("ERROR");
            }
            break;

        }
        if (terminals.find(matching.top()) != terminals.end()){
            if (matching.top() == tokens[i]->getTokenType()) {
                matching.pop();
            } else{
                outputs.push_back("ERROR");
            }
        } else{
            string stackTop = matching.top();
            matching.pop();
            NonTerminal* tempNonTerminal = nonTerminals.at(stackTop);
            if(tempNonTerminal->getParsingTable().find(tokens[i]->getTokenType()) != tempNonTerminal->getParsingTable().end()) {
                Production *tempProduction = tempNonTerminal->getParsingTable().at(tokens[i]->getTokenType());
                vector<string> productionStrings = tempProduction->getStrings();
                outputProduction(productionStrings);

                for (int j = productionStrings.size() - 1; j >= 0; j--) {
                    matching.push(productionStrings[j]);
                }
                i--;
            } else{
                outputs.push_back("ERROR");
            }
        }
    }
    writeTheOutput();
}

void Matcher::outputProduction(vector<string> production) {
    for (int i = 0; i < production.size() ; ++i) {
        outputs.push_back(production[i]);
    }

}

void Matcher::writeTheOutput() {
    ofstream myfile;
    myfile.open ("outputFile.txt");

    for (int i = 0; i < outputs.size(); i++) {
        myfile << outputs[i] << "\n";
    }

    myfile.close();
}



