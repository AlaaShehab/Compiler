//
// Created by Bassant on 3/25/2019.
//
#include "DFANode.h"
#include "Group.h"
#include <vector>
using namespace std;


Group::Group (int name) {
    Group::name = name;
}

void Group::setNext(int group) {
    nextGroups.push_back(group);
}

void Group::addState(DFANode* state) {
    states.push_back(state);
}

bool Group::contains(DFANode* node) {
    for (auto i = states.begin(); i != states.end(); i++) {
        if ((*i)->getName() == node->getName()) {  /////////// new dfa state name -- akram
            return true;
        }
    }
    return false;
}

bool Group::isStart() {
    return start;
}

bool Group::isAcceptance() {
    return acceptor;
}

void Group::setAcceptance() {
    acceptor = true;
}

void Group::setStart() {
    start = true;
}