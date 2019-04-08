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

using namespace std;



int main() {

    LexicalRuleParser dfa;
    dfa.readfile("D:\\Projects\\Compiler\\Lexical_Analyzer\\example.txt");
    dfa.parseRules();
    map<string, int> map = dfa.getPriority();





    return 0;
}


