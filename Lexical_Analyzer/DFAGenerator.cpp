//
// Created by akrammoussa on 22/03/19.
//

#define EPSILON '!'

#include <iostream>
#include "DFAGenerator.h"
#include<bits/stdc++.h>
using namespace std;


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

vector<Node*>  DFAGenerator::generateDFATable(vector<Node *> NFA , char* inputs) {
    DFANode* startNode = new DFANode();
    startNode->addName(NFA[0]->getName());
    startNode->setStartNode(true);
    DFANode* temp =startNode;

    bool finish = false;
    while (!finish){
        vector <int> tempName = temp->getNodeNameList();
        for (int i = 0; i < tempName.size(); ++i) {

        }
    }


}


