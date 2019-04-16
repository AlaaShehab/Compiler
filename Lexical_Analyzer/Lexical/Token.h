//
// Created by alaa on 3/25/2019.
//

#ifndef LEXICAL_ANALYZER_TOKEN_H
#define LEXICAL_ANALYZER_TOKEN_H

#include <string>

using namespace std;


class Token {

public:

    Token(string, string);

    void setTokenType(string);
    void setTokenValue(string);

    string getTokenType();
    string getTokenValue();

private:
    string value;
    string type;


};


#endif //LEXICAL_ANALYZER_TOKEN_H
