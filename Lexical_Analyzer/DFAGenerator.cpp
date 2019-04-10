//
// Created by akrammoussa on 22/03/19.
//

#include <iostream>
#include "DFAGenerator.h"
#include<bits/stdc++.h>
#include <queue>
#include "Transition.h"
char EPSILON[2] = "~";
using namespace std;

void fillInClosure(DFANode* node,vector<Node *> NFA){
    //todo after fixing the epsilon string
    vector<int> tempNodeNameList =node->getNodeNameList();
    for (int i = 0; i < tempNodeNameList.size(); ++i) {
        Node* tempNode;
        vector<int> listOfTransitions;
        for (int j = 0; j < NFA.size(); ++j) {
            if (NFA[j]->getName() == tempNodeNameList[i]) {
                tempNode = NFA[j];
                break;
            }
        }
        for (int j = 0; j < tempNode->getEpslonClosure().size(); ++j) {
            node->addToEpsilonClosure(tempNode->getEpslonClosure()[j]);
        }
    }

}

//can be optimized to return node directly
bool checkIfExists(vector<int> nameList , vector<DFANode *> DFA){
    set<int> newNodeName(nameList.begin(), nameList.end());
    for (int i = 0; i < DFA.size(); ++i) {
        vector<int> tempName = DFA[i]->getNodeNameList();
        set<int> existNodeName(tempName.begin(), tempName.end());
        if (newNodeName == existNodeName){
            return true;
        }
    }
    return false;
}
DFANode* getNodeFromName(vector<int> nodeNameList, vector<DFANode *> DFA){
    sort(nodeNameList.begin() , nodeNameList.end());
    for (int i = 0; i < DFA.size(); ++i) {
        vector<int> tempName = DFA[i]->getNodeNameList();
        sort(tempName.begin() , tempName.end());
        if (nodeNameList == tempName){
            return DFA[i];
        }
    }
}
void setEndNodes(vector<Node *> NFA,vector<DFANode *> DFA ){
    for (int i = 0; i < NFA.size(); ++i) {
        if(NFA[i]->isAcceptor()) {
            for (int j = 0; j < DFA.size(); ++j) {
                vector<int> tempNameList = DFA[j]->getEpslonClosure();
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

bool findTransitionOnInput (char* transitionInput, char input) {
    for (int i = 0; i < strlen(transitionInput); i++) {
        if (input == transitionInput[i]) {
            return true;
        }
    }
    return false;
}

vector<int> tranistionTo(char input, int target, vector<Node *> NFA) {
    //todo: it takes char inout and target from closure and return nextNodes when givin that input
    Node* tempNode;
    vector<int> listOfTransitions;
    for (int i = 0; i < NFA.size(); ++i) {
        if (NFA[i]->getName() == target) {
            tempNode = NFA[i];
            break;
        }
    }
    vector<Transition> tempTransitionList  = tempNode->getTransition();
    for (int j = 0; j <tempTransitionList.size() ; ++j) {
        if (findTransitionOnInput(tempTransitionList[j].getInput(), input)){
            listOfTransitions.push_back(tempTransitionList[j].getNode()->getName());
        }
    }
    return listOfTransitions;

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
            int index = s->getName();
            if (!visited[index]) {
                visited[index] = true;
                NFA[i]->addToEpsilonClosure(index);
            }
            vector<Transition> transition = s->getTransition();
            for (int i = 0; i < transition.size(); i++) {
                Node* temp = transition[i].getNode();
                if (!visited[temp->getName()] && (transition[i].getInput())[0] == EPSILON[0]) {
                    stack.push(temp);
                }
            }
        }
    }
}

vector<DFANode*>  DFAGenerator::generateDFATable(vector<Node *> NFA , vector<char> inputs,Node* start) {
    vector<DFANode *> DFA ;
    queue<DFANode *> buildingQueue;
    int nameCounter = 0;
    DFANode* startNode = new DFANode(nameCounter);
    nameCounter++;
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
            DFANode* newNode = new DFANode(nameCounter++);
            bool inputFound =false;
            for (int j = 0; j < tempClosure.size(); ++j) {
                vector<int> tempVector = tranistionTo(inputs[i] ,tempClosure[j] , NFA );
                for (int k = 0; k <tempVector.size() ; ++k) {
                    newNode->addName(tempVector[k]);
                    inputFound =true;
                }
            }
            char temp[2];
            temp[0] = inputs[i];
            temp[1] = '\0';
            if (inputFound) {
                if(!checkIfExists(newNode->getNodeNameList(),DFA)){
                    fillInClosure(newNode,NFA);
                    buildingQueue.push(newNode);
                    DFA.push_back(newNode);
                    tempNode->addTransition(Transition(newNode, temp));
                } else{
                    nameCounter --;
                    newNode = getNodeFromName(newNode->getNodeNameList(), DFA);
                    tempNode->addTransition(Transition(newNode, temp));
                }
            } else {
                nameCounter --;
            }
        }
        setEndNodes(NFA,DFA);
    }
    setEndNodes(NFA,DFA);
    return DFA;
}





