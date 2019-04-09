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
#include "TokenGenerator.h"
#include "Token.h"
#include "DFAGenerator.h"
using namespace std;



int main() {

    char EP[2] = "~";
    LexicalRuleParser nfa;
    nfa.readfile("D:\\Projects\\Compiler\\Lexical_Analyzer\\example.txt");
    nfa.parseRules();
    map<string, int> map = nfa.getPriority();

   DFAGenerator dfa = DFAGenerator();
   dfa.initializeClosureLists(nfa.getAllAutomataNodes());
   dfa.generateDFATable(nfa.getAllAutomataNodes(), nfa.getAutomataInput(), nfa.getNFAstartNode());


    return 0;
}


