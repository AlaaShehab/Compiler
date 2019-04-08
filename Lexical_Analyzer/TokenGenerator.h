//
// Created by alaa on 3/25/2019.
//

#ifndef LEXICAL_ANALYZER_TOKENGENERATOR_H
#define LEXICAL_ANALYZER_TOKENGENERATOR_H

#include <string>
#include <vector>
#include "DFANode.h"
#include "Token.h"
#include <string.h>
#include "Transition.h"
#include <map>

using namespace std;

class DFANode;
class Token;
class TokenGenerator {

public:
    TokenGenerator(DFANode*, map<string, int>);
    void tokenizeCode(string);
    Token* getNextToken();

private:
    //used for next token generation
    int pointer;

    DFANode* start;

    //the whole program that will be compiled
    string programCode;

    //lexical rules priorities
    map<string, int> priority;

    //tokens to be returned to print to file
    vector<Token*> tokens;

    //print tokens to file
    void printTokensToFile();

    void readProgram(string);

    bool findTransition(Transition, char);

    string getAccepted(vector<string>);

    int backTrack(int, DFANode *);

    bool setError(int, bool);

};


#endif //LEXICAL_ANALYZER_TOKENGENERATOR_H
