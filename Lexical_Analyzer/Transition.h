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
    Transition(Node*, char*);
    Transition();

    //methods
    Node setNext(Node*);
    Node setInput(char *);

    Node getNext();
    void getInput(char *);

private:
    Node* nextNode;
    char * input;
};


#endif //LEXICAL_ANALYZER_TRANSITION_H
