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
using namespace std;
void dfa( char * c);

int main() {

    LexicalRuleParser dfa;
    dfa.readfile("D:\\Projects\\Compiler\\Lexical_Analyzer\\example.txt");
    dfa.parseRules();
<<<<<<< HEAD
    //vector<Node *> autom = dfa.getAutotmatas();

=======
>>>>>>> parsingTxtFile

    return 0;
}
