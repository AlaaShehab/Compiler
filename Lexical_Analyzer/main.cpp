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

#include "Syntax_Analyzer/Production.h"
#include "Syntax_Analyzer/NonTerminal.h"
#include "Syntax_Analyzer/GrammarParser.h"
#include "Syntax_Analyzer/FirstAndFollowGenerator.h"
#include "Syntax_Analyzer/TableGenerator.h"
#include "Syntax_Analyzer/ConvertGrammar.h"

using namespace std;

int main() {

/*
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
    */




    GrammarParser parser = GrammarParser();
    parser.readFile("D:\\Projects\\Compiler\\Lexical_Analyzer\\Syntax_Analyzer\\grammar.txt");
    parser.parseGrammar();

    set<string> terminals = parser.getTerminals();
    map<string, NonTerminal*> nonTerminals = parser.getNonTerminals();

    ConvertGrammar converter = ConvertGrammar(nonTerminals, terminals);
    nonTerminals = converter.convert();

    FirstAndFollowGenerator firstNfollow = FirstAndFollowGenerator(nonTerminals, terminals);
    firstNfollow.getAllFirst();
    firstNfollow.getAllFollow();

    TableGenerator table = TableGenerator();
    table.prepareAllTables(nonTerminals, terminals);



    return 0;
}


