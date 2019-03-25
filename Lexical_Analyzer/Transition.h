//
// Created by alaa on 3/18/2019.
//

#ifndef LEXICAL_ANALYZER_TRANSITION_H
#define LEXICAL_ANALYZER_TRANSITION_H

#include "Node.h"
#include <string>

class Node;
class Transition {
public:
    //constructors
    Transition(Node *, char *);
    Transition();

    //methods
    void setNext(Node*);
    void setInput(char *);

    Node* getNode();
    char* getInput();

    char EPSILON[2] = "~";
private:
    Node* nextNode;
    char* input;
};


#endif //LEXICAL_ANALYZER_TRANSITION_H
