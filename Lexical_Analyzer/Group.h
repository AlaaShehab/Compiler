//
// Created by Bassant on 3/25/2019.
//

#ifndef LEXICAL_ANALYZER_GROUP_H
#define LEXICAL_ANALYZER_GROUP_H
#include "DFANode.h"
#include <vector>

using namespace std;


class Group {

public:
    void addState(int); // int indicate state name
    void setNext(int);  // int indicate Group name
 private:
    int name;
    vector<DFANode*> states;
    vector<int> nextGroups;
};


#endif //LEXICAL_ANALYZER_GROUP_H
