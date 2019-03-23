//
// Created by alaa on 3/18/2019.
//

#ifndef LEXICAL_ANALYZER_DFANODE_H
#define LEXICAL_ANALYZER_DFANODE_H

#include "Node.h"
#include <vector>

class DFANode: public Node{

public:

    void addName (int);
    vector<int> getNodeNameList();

private:
    vector<int> nodeNameList;


};


#endif //LEXICAL_ANALYZER_DFANODE_H
