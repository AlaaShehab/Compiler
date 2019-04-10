//
// Created by alaa on 3/18/2019.
//

#include "DFANode.h"


DFANode::DFANode(int name):Node(name) {}

DFANode::DFANode(string type, int name):Node(type,name) {}

void DFANode::addName(int name) {
    nodeNameList.push_back(name);
}

const vector<int> DFANode::getNodeNameList() {
    return nodeNameList;
}

vector<string> DFANode::getTypesAccepted() {
    return typesAccepted;
}
void DFANode::addToTypesAccepted(string name) {
    typesAccepted.push_back(name);
}

void DFANode::setTypesAccepted(vector<string> types) {
    typesAccepted = types;
}
