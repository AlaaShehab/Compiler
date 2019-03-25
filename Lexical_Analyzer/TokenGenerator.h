//
// Created by alaa on 3/25/2019.
//

#ifndef LEXICAL_ANALYZER_TOKENGENERATOR_H
#define LEXICAL_ANALYZER_TOKENGENERATOR_H

#include <string>
#include <vector>
#include "DFANode.h"
#include "Token.h"

using namespace std;

class DFANode;
class Token;
class TokenGenerator {

public:
    TokenGenerator(DFANode*);
    void tokenizeCode(string);
    Token* getNextToken();

private:
    //used for next token generation
    int pointer;

    DFANode* start;

    //the whole program that will be compiled
    string programCode;

    //tokens to be returned to print to file
    vector<Token*> tokens;

    //print tokens to file
    void printTokensToFile();

    void readProgram(string);



};


#endif //LEXICAL_ANALYZER_TOKENGENERATOR_H
