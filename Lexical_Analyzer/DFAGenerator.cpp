//
// Created by akrammoussa on 22/03/19.
//

#include "DFAGenerator.h"


void DFAGenerator::initializeClousreLists(vector<Node *> NFA) {

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


