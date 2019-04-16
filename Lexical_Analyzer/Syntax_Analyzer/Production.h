//
// Created by alaa on 4/16/2019.
//

#ifndef LEXICAL_ANALYZER_PRODUCTION_H
#define LEXICAL_ANALYZER_PRODUCTION_H

#include <string>
#include "vector"

using namespace std;

class Production {

public:
    vector<string> getStrings();
    string getStringAt(int);
    void addStringToProduction(string);
private:
    vector<string> strings;

};


#endif //LEXICAL_ANALYZER_PRODUCTION_H
