//
// Created by alaa on 3/25/2019.
//

#include "TokenGenerator.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Token.h"

using namespace std;

void TokenGenerator::tokenizeCode(string fileName) {
    readProgram(fileName);
    /*
     * loop on input string
     * for each input check current node to find a transition using this node
     * if found then go to next node and if it is end state then
     * set a counter to current length of input and continue
     * if no input match to a transition skip this character
     * or backtrack and check if it's accepted by any type
     *
     * When u find a match add token and start again from beg
     * and make counter of length = 0
     *
     * to find a char in a transition loop on all transitions and
     * all their input
     */
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

TokenGenerator::TokenGenerator(DFANode * start) {
    TokenGenerator::start = start;
    pointer = 0;
    programCode = "";
}

Token* TokenGenerator::getNextToken() {
    if (pointer == tokens.size()) {
        return nullptr;
    }
    return tokens[pointer++];
}