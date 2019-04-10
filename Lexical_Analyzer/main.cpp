#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <regex>
#include <stack>
#include "Node.h"
#include "LexicalRuleParser.h"
#include "Transition.h"
#include <set>
#include <map>
#include "DFANode.h"
#include "minimization.h"
#include "DFAGenerator.h"
#include "TokenGenerator.h"

using namespace std;

int main() {


    LexicalRuleParser nfa;
    nfa.readfile("D:\\Projects\\Compiler\\Lexical_Analyzer\\grammar.txt");
    nfa.parseRules();
    map<string, int> map1 = nfa.getPriority();

   DFAGenerator dfa = DFAGenerator();
   dfa.initializeClosureLists(nfa.getAllAutomataNodes());
   vector<DFANode*> DFA= dfa.generateDFATable(nfa.getAllAutomataNodes(), nfa.getAutomataInput(), nfa.getNFAstartNode());

    DFANode* start = DFA[0];


    TokenGenerator generator = TokenGenerator(start, map1);
    generator.tokenizeCode("D:\\Projects\\Compiler\\Lexical_Analyzer\\program.txt");

    return 0;
}


