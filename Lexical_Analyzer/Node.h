//
// Created by alaa on 3/18/2019.
//

#ifndef LEXICAL_ANALYZER_NODE_H
#define LEXICAL_ANALYZER_NODE_H
#include <string>
#include <list>
#include <vector>
#include "Transition.h"

using namespace std;
class Transition;
class Node {
public:
    //constructors
    Node (string type = "", int name = -1);
    Node (int name = -1);
    Node ();

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
    vector<Transition> getTransition();
    Node getNext ();

private:
    //variables
    string type;
    int name;
    bool acceptor;
    bool start;

    //list of transitions for a node
    vector<Transition> transitionList;

};


#endif //LEXICAL_ANALYZER_NODE_H
