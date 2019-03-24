//
// Created by akrammoussa on 22/03/19.
//

#ifndef LEXICAL_ANALYZER_DFAGENERATOR_H
#define LEXICAL_ANALYZER_DFAGENERATOR_H


#include "Node.h"
#include "DFANode.h"

class DFAGenerator {
public:
    void initializeClousreLists(vector<Node*>);
    vector<Node*> generateDFATable(vector<Node*>,char*);


};


#endif //LEXICAL_ANALYZER_DFAGENERATOR_H
