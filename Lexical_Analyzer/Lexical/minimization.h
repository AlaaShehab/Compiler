
#ifndef LEXICAL_ANALYZER_MINIMIZATION_H
#define LEXICAL_ANALYZER_MINIMIZATION_H


#include "Node.h"
#include "DFANode.h"
#include "Group.h"
#include <list>
#include <queue>
#include <vector>
#include "Transition.h"
#include <map>


class minimization {

public:
    minimization(vector<DFANode*>, vector<char>, map<string, int>);


    int getNextState(int, DFANode*);
    void setTransitions();
    void startMinimization();   //set first two groups acc/normal
    void getCurrLevelGroups();  // enqueue groups and add them to current group list
    void minimize(); // loop to do actual minimization
    int getGroup(DFANode*);
    void checkGroup(DFANode*);
    bool sameStates(Group*);
    void switchGroups();
    void print();
    void addGroupState(Group*, int);
    DFANode* finalOutput();
    vector<Group*> currentGroups;
    vector<Group*> nextGroups;
    vector<DFANode*> dfaNodes;
    vector<DFANode*> finalStates;
    vector<char> inputs;
    vector<int> nexts;
    int count = 2;

    map<string, int> map1;

};

#endif //LEXICAL_ANALYZER_MINIMIZATION_H