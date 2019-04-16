//
// Created by alaa on 3/25/2019.
//

#include "Token.h"

Token::Token(string type, string value) {
    Token::type = type;
    Token::value = value;
}

string Token::getTokenType() {
    return type;
}

string Token::getTokenValue() {
    return value;
}

void Token::setTokenType(string type) {
    Token::type = type;
}

void Token::setTokenValue(string value) {
    Token::value = value;
}