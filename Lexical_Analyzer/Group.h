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
    Group(int);
    //functions
    void addState(DFANode*); // int indicate state name
    void setNext(int);  // int indicate Group name
    bool contains(DFANode*);
    bool isAcceptance();
    bool isStart();
    void setAcceptance();
    void setStart();

    //variables
    int name;
    vector<DFANode*> states;
    vector<int> nextGroups;
    bool acceptor = false;
    bool start = false;
};


#endif //LEXICAL_ANALYZER_GROUP_H
