//
// Created by alaa on 3/18/2019.
//

#include "DFANode.h"

void DFANode::addName(int name) {
    nodeNameList.push_back(name);
}
void DFANode::addClosure(int name) {
    closureList.push_back(name);
}

vector<int> DFANode::getNodeNameList() {
    return nodeNameList;
}

const vector<int> &DFANode::getClosureList() const {
    return closureList;
}
