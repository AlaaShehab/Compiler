//
// Created by alaa on 3/18/2019.
//

#ifndef LEXICAL_ANALYZER_DFANODE_H
#define LEXICAL_ANALYZER_DFANODE_H

#include "Node.h"
#include <list>

class DFANode: public Node{

public:
    DFANode();
    void addName (int);
    void addClosure(int);
    const vector<int> getNodeNameList();
    vector<string> getTypesAccepted();

private:
    vector<string> typesAccepted;
    vector<int> nodeNameList;




};


#endif //LEXICAL_ANALYZER_DFANODE_H
