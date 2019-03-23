//
// Created by akrammoussa on 22/03/19.
//

#ifndef LEXICAL_ANALYZER_DFAGENERATOR_H
#define LEXICAL_ANALYZER_DFAGENERATOR_H


#include "Node.h"

class DFAGenerator {
public:
    void initializeClosureLists(vector<Node*>);
    vector<Node*> generateDFATable(vector<Node*>);


};


#endif //LEXICAL_ANALYZER_DFAGENERATOR_H
