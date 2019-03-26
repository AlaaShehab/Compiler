//
// Created by akrammoussa on 22/03/19.
//

#define EPSILON '!'
#include <iostream>
#include "DFAGenerator.h"
#include<bits/stdc++.h>
#include <queue>
#include "Transition.h"
using namespace std;

void fillInClosure(DFANode*,vector<Node *>){
    //todo
}

bool checkIfExists(vector<int> nameList , vector<DFANode *> DFA){

}
DFANode* getNodeFromName(vector<int> nodeNameList, vector<DFANode *> DFA){
    //todo
}
void setEndNodes(vector<Node *> NFA,vector<DFANode *> DFA ){
    for (int i = 0; i < NFA.size(); ++i) {
        if(NFA[i]->isAcceptor()) {
            for (int j = 0; j < DFA.size(); ++j) {
                vector<int> tempNameList = DFA[j]->getNodeNameList();
                for (int k = 0; k < tempNameList.size(); ++k) {
                        if (NFA[i]->getName() == tempNameList[k]){
                            DFA[j]->setAcceptorNode(true);
                            DFA[j]->addToTypesAccepted(NFA[i]->getType());
                            break;
                        }
                }
            }
        }
    }
}

vector<int> tranistionTo(char *input, int target, vector<Node *> NFA) {
    //todo: it takes char inout and target from closure and return nextNodes when givin that input
}
void DFAGenerator::initializeClosureLists(vector<Node *> NFA) {

    for (int i = 0; i < NFA.size(); ++i) {
        vector <bool> visited;
        for(int k = 0; k < NFA.size(); k++) visited.push_back(false);
        stack<Node *> stack;
        stack.push(NFA[i]);
        while (!stack.empty()) {
            Node * s = stack.top();
            stack.pop();
            //vector<Node *>::iterator it = find(NFA.begin(), NFA.end(), s);
            int index = s->getName();
            if (!visited[index]) {
                visited[index] = true;
                NFA[i]->addToEpsilonClosure(index);
            }
            for (auto j = s->getTransition().begin(); j != s->getTransition().end(); ++j)
                if (!visited[j.operator*().getNode()->getName()] && *(j.operator*().getInput()) == EPSILON)
                    stack.push(j.operator*().getNode());
        }
    }
}

vector<Node*>  DFAGenerator::generateDFATable(vector<Node *> NFA , vector<char*> inputs,Node* start) {
    vector<DFANode *> DFA ;
    queue<DFANode *> buildingQueue;
    DFANode* startNode = new DFANode();
    startNode->addName(start->getName());
    startNode->setStartNode(true);
    fillInClosure(startNode,NFA);
    DFA.push_back(startNode);
    buildingQueue.push(startNode);
    while (buildingQueue.size() != 0){
        DFANode* tempNode;
        tempNode = buildingQueue.front();
        buildingQueue.pop();
        vector<int> tempClosure = tempNode->getEpslonClosure();
        for (int i = 0; i < inputs.size() ; ++i) {
            DFANode* newNode = new DFANode();
            for (int j = 0; j < tempClosure.size(); ++j) {
                vector<int> tempVector = tranistionTo(inputs[i] ,tempClosure[j] , NFA );
                for (int k = 0; k <tempVector.size() ; ++k) {
                    newNode->addName(tempVector[k]);
                }
            }
            if(!checkIfExists(newNode->getNodeNameList(),DFA)){
                fillInClosure(newNode,NFA);
                buildingQueue.push(newNode);
                tempNode->addTransition(Transition(newNode, inputs[i]));
            } else{
                newNode = getNodeFromName(newNode->getNodeNameList(),DFA);
                tempNode->addTransition(Transition(newNode, inputs[i]));
            }
        }
        setEndNodes(NFA,DFA);
    }
}





