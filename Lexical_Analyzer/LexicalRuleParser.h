//
// Created by alaa on 3/20/2019.
//

#ifndef LEXICAL_ANALYZER_LEXICALRULEPARSER_H
#define LEXICAL_ANALYZER_LEXICALRULEPARSER_H
#include <string>
#include "Node.h"
#include <stack>
#include <vector>

using namespace std;

class LexicalRuleParser {
public:
    void readfile (string);
    void parseRules();
    //return char array of input that is sent as parameter
    vector<char> getAutomataInput ();
    vector<Node*> getAutotmatas ();
    vector<Node*> getAllAutomataNodes ();

    //static const string LAMDA = "\L";



private:
    int nodesID;
    list<string> rules;

    list<string> expressionList;
    list<string> definitionList;
    list<string> keywordList;
    list<string> punctuationList;

    void groupRules();
    void findRuleType(string);

    void createKeywordAutomata();
    void createPuncAutomata();
    void createExpAutomata();
    void createDefinAutomata();


    void buildKeywordAutomataGraph(vector<string>);
    void buildPunctAutomataGraph(vector<string>);
    vector<string> split(string, char);

    //don't forget to remove duplicates
    vector<Node*> automataNodes;
    vector<Node*> automatas;
    vector<char> automataInputs;








};


#endif //LEXICAL_ANALYZER_LEXICALRULEPARSER_H
