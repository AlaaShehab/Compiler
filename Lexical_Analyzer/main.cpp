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
void dfa( char * c);

int main() {

    LexicalRuleParser dfa;
    dfa.readfile("D:\\Projects\\Compiler\\Lexical_Analyzer\\example.txt");
    dfa.parseRules();

    map<string, int> gquiz1;
    map<string,int>::iterator it;
    // insert elements in random order
    gquiz1.insert(pair<string, int>("alaa", 30));
    gquiz1.insert(pair<string, int>("akram", 60));
    gquiz1.insert(pair<string, int>("bassant", 20));
    gquiz1.insert(pair<string, int>("islam", 10));

    it = gquiz1.find("alaa");
    int max = std::min_element(gquiz1.begin(), gquiz1.end())->second;

    cout << max;
    if (it != gquiz1.end()){
       // cout << "element found =  " << it->second << endl;
    }


    return 0;
}
