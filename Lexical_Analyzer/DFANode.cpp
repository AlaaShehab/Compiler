//
// Created by alaa on 3/18/2019.
//

#include "DFANode.h"



void DFANode::addName(int name) {
    nodeNameList.push_back(name);
}

const vector<int> DFANode::getNodeNameList() {
    return nodeNameList;
}

vector<string> DFANode::getTypesAccepted() {
    return typesAccepted;
}

