//
// Created by alaa on 3/18/2019.
//

#include "Node.h"
#include <string>
#include <list>
#include "Transition.h"

using namespace std;

//constructors
Node::Node (string type, int name) {
    Node::type = type;
    Node::name = name;
    Node::acceptor = false;
    Node::start = false;
}
Node::Node (int name) {
    Node::name = name;
    Node::acceptor = false;
    Node::start = false;
}
Node::Node () {
    Node::acceptor = false;
    Node::start = false;
}

//methods
void Node::setType(string type) {
    Node::type = type;
}
void Node::setName(int name) {
    Node::name = name;
}
string Node::getType() {
    return type;
}
int Node::getName() {
    return name;
}

void Node::setAcceptorNode(bool acceptor) {
    Node::acceptor = acceptor;
}
void Node::setStartNode(bool start) {
    Node::start = start;
}

bool Node::isAcceptor() {
    return acceptor;
}
bool Node::isStart() {
    return start;
}

void Node::addTransition(Transition transition) {
    transitionList.push_back(transition);
}
vector<Transition> Node::getTransition() {
    return transitionList;
}

Node Node::getNext() {
    return transitionList.front().getNext();
}