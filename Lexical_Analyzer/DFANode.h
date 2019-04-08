//
// Created by alaa on 3/18/2019.
//

#ifndef LEXICAL_ANALYZER_DFANODE_H
#define LEXICAL_ANALYZER_DFANODE_H

#include "Node.h"
#include <list>

class DFANode: public Node{

public:
    DFANode(int);
    DFANode(string, int);

    void addName (int);
    void addClosure(int);
    const vector<int> getNodeNameList();
    vector<string> getTypesAccepted();
    void setTypeAccepted(string);

private:
    vector<string> typesAccepted;
    vector<int> nodeNameList;




};


#endif //LEXICAL_ANALYZER_DFANODE_H
