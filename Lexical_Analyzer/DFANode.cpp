//
// Created by alaa on 3/18/2019.
//

#include "DFANode.h"

void DFANode::addName(int name) {
    nodeNameList.push_back(name);
}

list<int> DFANode::getNodeNameList() {
    return nodeNameList;
}