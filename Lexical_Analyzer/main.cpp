#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <regex>
#include <stack>
#include "Lexical/Node.h"
#include "Lexical/LexicalRuleParser.h"
#include "Lexical/Transition.h"
#include <set>
#include <map>
#include "Lexical/DFANode.h"
#include "Lexical/minimization.h"
#include "Lexical/DFAGenerator.h"
#include "Lexical/TokenGenerator.h"

using namespace std;

int main() {


    LexicalRuleParser nfa;
    nfa.readfile("D:\\Projects\\Compiler\\Lexical_Analyzer\\Lexical\\grammar.txt");
    nfa.parseRules();
    map<string, int> map1 = nfa.getPriority();

   DFAGenerator dfa = DFAGenerator();
   dfa.initializeClosureLists(nfa.getAllAutomataNodes());
   vector<DFANode*> DFA= dfa.generateDFATable(nfa.getAllAutomataNodes(), nfa.getAutomataInput(), nfa.getNFAstartNode());

    DFANode* start = DFA[0];


    TokenGenerator generator = TokenGenerator(start, map1);
    generator.tokenizeCode("D:\\Projects\\Compiler\\Lexical_Analyzer\\Lexical\\program.txt");

    return 0;
}


