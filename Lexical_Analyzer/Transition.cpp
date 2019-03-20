//
// Created by alaa on 3/18/2019.
//

#include "Transition.h"
#include "Node.h"
#include <string.h>

using namespace std;

Transition::Transition(Node* nextNode, char* input) {
    Transition::nextNode = nextNode;
    Transition::input = new char[strlen(input)+1];
    strcpy(Transition::input, input);
}

Transition::Transition() {
}

void Transition::getInput(char * input) {
    input = new char[strlen(Transition::input)+1];
    strcpy(input, Transition::input);
}

Node* Transition::getNext() {
    return nextNode;
}

Node Transition::setInput(char * input) {
    Transition::input = new char[strlen(input)+1];
    strcpy(Transition::input, input);
}

Node Transition::setNext(Node* nextNode) {
    Transition::nextNode = nextNode;
}