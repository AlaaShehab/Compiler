#ifndef LEXICAL_ANALYZER_DFAGENERATOR_H
#define LEXICAL_ANALYZER_DFAGENERATOR_H


#include "Node.h"
#include "DFANode.h"

class DFAGenerator {
public:
    void initializeClosureLists(vector<Node*>);
    vector<Node*> generateDFATable(vector<Node*>,vector<char*>,Node*);

};


#endif //LEXICAL_ANALYZER_DFAGENERATOR_H
