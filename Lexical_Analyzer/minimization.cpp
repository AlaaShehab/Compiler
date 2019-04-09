
#include "minimization.h"
#include "Node.h"
#include "DFANode.h"
#include "Group.h"
#include <list>
#include <iostream>
#include <utility>
#include <queue>
#include <vector>
#include "Transition.h"
#include <string>
#include <cstring>

using namespace std;

minimization::minimization(vector<DFANode*> nodes, vector<char> input) {
    minimization::dfaNodes = nodes;
    minimization::inputs = input;
}

void minimization::startMinimization() {
    Group* accStates = new Group(0);
    Group* normalStates = new Group(1);
    accStates->setAcceptance();
    for (int it = 0; it < dfaNodes.size(); it++)
        if (dfaNodes[it]->isAcceptor()) {
            accStates->addState(dfaNodes[it]);
            if (dfaNodes[it]->isStart()) {
                accStates->setStart();
            }
        } else {
            normalStates->addState(dfaNodes[it]);
            if (dfaNodes[it]->isStart()) {
                normalStates->setStart();
            }
        }
    currentGroups.push_back(normalStates);
    currentGroups.push_back(accStates);
    minimize();
}

void minimization::getCurrLevelGroups() {
    int i =0;
    currentGroups.clear();
    while (!nextGroups.empty()) {
        currentGroups.push_back(nextGroups[i]);
        i++;
    }
}

void minimization::minimize() {
    while (true){
        for(int i = 0; i < currentGroups.size(); i++) {
            Group* group = currentGroups[i];
            for(int j = 0; j < group->states.size(); j++) {
                DFANode* groupState = group->states[j];
                addGroupState(group, j);
                if (group->states.size() > 1) {
                    checkGroup(groupState);
                } else {
                    for (int i = 0; i < nexts.size(); i++) {
                        group->nextGroups.push_back(nexts[i]);
                    }
                    nextGroups.push_back(group);
                }
            }
        }
        if (currentGroups.size()== nextGroups.size()) {
            break;
        } else {
            switchGroups();
        }
    }
    print();
}

int minimization::getGroup(DFANode* node) {
    int j = 0;
    for(int i = 0; i < currentGroups.size(); i++) {
        if (currentGroups[i]->contains(node)) {
            return j;
        }
        j++;
    }
}

void minimization::checkGroup(DFANode* node) {
    bool added = false;
    for(int i = 0; i < nextGroups.size(); i++) {
        sameStates(nextGroups[i]);
        if(sameStates(nextGroups[i])) {
            if ((node->isAcceptor() == nextGroups[i]->isAcceptance())) {
                nextGroups[i]->addState(node);
                added = true;
            }
        }
    }
    if (!added) {
        Group* temp = new Group(count);
        if (node->isStart()) {
            temp->setStart();
        }
        if (node->isAcceptor()) {
            temp->setAcceptance();
        }
        count++;
        temp->addState(node);
        for(int i = 0; i < nexts.size(); i++) {
            temp->nextGroups.push_back(nexts[i]);
        }
        nextGroups.push_back(temp);
    }
    nexts.clear();
}

bool minimization::sameStates(Group* group) {
    for(int i = 0; i < group->nextGroups.size(); i++) {
        if (group->nextGroups[i] != nexts[i]){
            return false;
        }
    }
    return true;
}

void minimization::switchGroups(){
    currentGroups.clear();
    for(int i = 0; i < nextGroups.size(); i++) {
        currentGroups.push_back(nextGroups[i]);
    }
    nextGroups.clear();
}

void minimization::print(){
    for(int i = 0; i < nextGroups.size(); i++) {
        cout << nextGroups[i]->name;
        cout << "\n";
        for (int j = 0; j < nextGroups[i]->nextGroups.size(); j++){
            cout << nextGroups[i]->nextGroups[j];
            cout << " ";
        }
        cout << "\n";
    }
    cout << "done";
}

void minimization::addGroupState(Group *group, int num) {
    nexts.clear();
    DFANode* groupState = group->states[num];
    for(int k = 0; k < inputs.size() && (group->nextGroups.size() == 0); k++) {
        bool found = false;
        for(int tl = 0; tl < groupState->getTransition().size(); tl++) {
            Transition trans = groupState->getTransition()[tl];
            for (int t = 0 ; t < strlen(trans.getInput()) ; t++) {
                if(trans.getInput()[t] == inputs[k]) {
                    nexts.push_back(getGroup((DFANode *)trans.getNode()));
                    found = true;
                }
            }
        }
        if (!found) {
            nexts.push_back(-1);

        }
    }

}

void minimization::finalOutput() {
    /*//acceptor
    vector<DFANode*> finalStates;
    for (int i = 0; i < nextGroups.size(); i++) {
        DFANode* temp = new DFANode(to_string(nextGroups[i]->name), nextGroups[i]->name);
        temp->setAcceptorNode(nextGroups[i]->isAcceptance());
        temp->setStartNode(nextGroups[i]->isStart());
        // TODO fadl el part bta3 el transitions
    }*/
}