//
// Created by alaa on 3/25/2019.
//

#include "TokenGenerator.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include "Transition.h"
#include <map>
#include "Token.h"

using namespace std;

TokenGenerator::TokenGenerator(DFANode * start, map<string, int> priority) {
    TokenGenerator::start = start;
    TokenGenerator::priority = priority;
    pointer = 0;
    programCode = "";

}

void TokenGenerator::tokenizeCode(string fileName) {
    readProgram(fileName);


    DFANode * current = start;

    int lastAcceptedChar = -1;
    DFANode * lastAcceptedNode;

    bool concatError = false;

    bool transFound = false;

    for (int i = 0; i < programCode.length(); i++) {
        transFound = false;
        //skip spaces and new lines;
        if (programCode[i] == ' ' || programCode[i] == '\n' || programCode[i] == '\t') {
            if (i != 0) {
                concatError = setError(lastAcceptedChar, concatError);
            }
            i = backTrack(lastAcceptedChar, lastAcceptedNode);
            lastAcceptedChar = -1;

            current = start;
            continue;
        }
        vector<Transition> transitions = current->getTransition();
        for (int j = 0; j < transitions.size(); j++){
           if (findTransition(transitions[j], programCode[i])) {
               transFound = true;
               char ch = programCode[i];
               current = (DFANode*)transitions[j].getNode();
               if (current->isAcceptor()) {
                   lastAcceptedChar = i;
                   lastAcceptedNode = current;
               }
               if (i == programCode.length() - 1) {
                   i = backTrack(lastAcceptedChar, lastAcceptedNode);
                   concatError = setError(lastAcceptedChar, concatError);
                   lastAcceptedChar = -1;
                   current = start;
               }
               break;
           }
        }
        if (!transFound) {
            i = backTrack(lastAcceptedChar, lastAcceptedNode);
            concatError = setError(lastAcceptedChar, concatError);
            lastAcceptedChar = -1;
            current = start;
        }

    }


    printTokensToFile();

}

int TokenGenerator::backTrack(int lastAcceptedChar, DFANode * lastAcceptedNode) {
    if (lastAcceptedChar == -1) {
        programCode = programCode.substr(1, programCode.length() - 1);
    } else {
        string type = getAccepted(lastAcceptedNode->getTypesAccepted());
        tokens.push_back(new Token(type, programCode.substr(0, lastAcceptedChar + 1)));
        int remaining = programCode.length() - lastAcceptedChar - 1;
        programCode = programCode.substr(lastAcceptedChar + 1, remaining);
    }
    return -1;
}

bool TokenGenerator::setError(int index, bool concatenateError) {
    if (index == -1 && !concatenateError) {
        tokens.push_back(new Token("ERROR", ""));
    } else if (index != -1) {
        return false;
    }
    return true;

}

string TokenGenerator::getAccepted(vector<string> acceptedTypes) {
    int min = 100;
    string type;
    map<string, int>::iterator it;
    for (int i = 0; i < acceptedTypes.size(); i++) {
        it = priority.find(acceptedTypes[i]);
        if (it != priority.end()){
            if (it->second < min) {
                type = it->first;
                min = it->second;
            }
        }
    }
    return type;
}

bool TokenGenerator::findTransition(Transition transition, char ch) {
    char * input = transition.getInput();
    for (int i = 0; i < strlen(input); i++) {
        if (ch == input[i]) {
            return true;
        }
    }
    return false;

}

void TokenGenerator::readProgram(string fileName) {
    string line;
    ifstream codeFile(fileName);
    if (codeFile.is_open())
    {
        while (getline(codeFile,line))
        {
            programCode = programCode + " " + line;
        }
        codeFile.close();
    } else {
        cout << "file cannot be opened" << endl;
    }
}

void TokenGenerator::printTokensToFile() {

    ofstream myfile;
    myfile.open ("D:\\Projects\\Compiler\\Lexical_Analyzer\\outputFile.txt");

    for (int i = 0; i < tokens.size(); i++) {
        myfile << tokens[i]->getTokenType() << "\n";
    }

    myfile.close();
}


Token* TokenGenerator::getNextToken() {
    if (pointer == tokens.size()) {
        return nullptr;
    }
    return tokens[pointer++];
}