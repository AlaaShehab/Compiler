//
// Created by alaa on 3/18/2019.
//

#ifndef LEXICAL_ANALYZER_NODE_H
#define LEXICAL_ANALYZER_NODE_H
#include <string>
#include <list>
#include "Transition.h"

using namespace std;
class Node {
public:
    //constructors
    Node (string, int);
    Node (int);

    //methods
    void setType(string);
    string getType();

    void setName(int);
    int getName();

    void setAcceptorNode(bool);
    void setStartNode(bool);

    bool isAcceptor();
    bool isStart();

    void addTransition (Transition);
    list<Transition> getTransition();

private:
    //variables
    string type;
    int name;
    bool acceptor;
    bool start;

    //list of transitions for a node
    list<Transition> transitionList;

};


#endif //LEXICAL_ANALYZER_NODE_H
