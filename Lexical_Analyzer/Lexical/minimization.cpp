
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
#include <map>
#include "TokenGenerator.h"

using namespace std;

minimization::minimization(vector<DFANode*> nodes, vector<char> input, map<string, int> map1) {
    minimization::dfaNodes = nodes;
    minimization::inputs = input;
    minimization::map1 = map1;
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
    finalOutput();
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
                    group->nextGroups.clear();
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
}

int minimization::getGroup(DFANode* node) {
    int j = 0;
    for(int i = 0; i < currentGroups.size(); i++) {
        if (currentGroups[i]->contains(node)) {
            return currentGroups[i]->name;
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
}

void minimization::addGroupState(Group *group, int num) {
    nexts.clear();
    DFANode* groupState = group->states[num];
    for(int k = 0; k < inputs.size() && (group->nextGroups.size() >= 0); k++) {
        bool found = false;
        for(int tl = 0; tl < groupState->getTransition().size(); tl++) {
            Transition trans = groupState->getTransition()[tl];
            for (int t = 0 ; t < strlen(trans.getInput()) ; t++) {
                if(trans.getInput()[t] == inputs[k]) {
                    int temp = getGroup((DFANode *)trans.getNode());
                    nexts.push_back(temp);
                    found = true;
                }
            }
        }
        if (!found) {
            nexts.push_back(-1);

        }
    }

}

DFANode* minimization::finalOutput() {
    for (int i = 0; i < nextGroups.size(); i++) {
        string type = nextGroups[i]->states[0]->getType();
        DFANode* temp = new DFANode(type, nextGroups[i]->name);
        temp->setAcceptorNode(nextGroups[i]->isAcceptance());
        temp->setStartNode(nextGroups[i]->isStart());
        temp->setTypesAccepted(nextGroups[i]->states[0]->getTypesAccepted());
        finalStates.push_back(temp);
    }
    setTransitions();
    DFANode* start = finalStates[0];

    TokenGenerator generator = TokenGenerator(start, map1);
    generator.tokenizeCode("D:\\Projects\\Compiler\\Lexical_Analyzer\\program.txt");
    return start;
}

int minimization::getNextState(int groupNum, DFANode* node){
    for (int i = 0; i < nextGroups.size(); ++i) {
        if(nextGroups[i]->name == groupNum || nextGroups[i]->contains(node)){
            return i;
        }
    }
}

void minimization::setTransitions(){
    for (int i = 0; i < finalStates.size(); i++) {
        int size = nextGroups[i]->states[0]->getTransition().size();
        for (int j = 0, k = 0; k < nextGroups[i]->nextGroups.size()&& size > 0 && j < size; j++, k++) {
            DFANode* node = (DFANode*)nextGroups[i]->states[0]->getTransition()[j].getNode();
            DFANode* toState;
            if (nextGroups[i]->states[0]->getTransition()[j].getInput()[0] != inputs[k]) {
                toState = NULL;
                j--;
            } else {
                toState = finalStates[getNextState(nextGroups[i]->nextGroups[k], node)];
                char c[2];
                c[0] = inputs[k];
                c[1] = '\0';
                finalStates[i]->addTransition(Transition(toState, c));
            }

        }
    }
}
