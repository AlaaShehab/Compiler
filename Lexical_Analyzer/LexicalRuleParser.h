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
    char EPSILON = '!';


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
    void buildDefinAutomataGraph(string);

    vector<string> split(string, char);

    //TODO don't forget to remove duplicates
    //TODO don't forget to minimize node so that no 2 epsilons are after each other
    //TODO don't forget to add all nodes at the end\
    // TODO make automata Input a set
    vector<Node*> automataNodes;
    vector<Node*> automatas;
    vector<char> automataInputs;

    /*
     * used with definitions that are just helping | building parts of
     * regular expressions|definitions
    */
    vector<string> helpingNotations;
    vector<Node *> helpingAutomatas;

    /*
     * add name of a definition to list for later use
     */
    void getDefinitionNotation(string);


    int precedence (char);
    char* getRange(char, char);


    Node * concatenateExpression(Node *, Node *);
    Node * orExpression(Node *, Node *);
    Node * positiveClosureExp(Node *);
    Node * kleenClosureExp(Node *);
    Node * rangeExpression(Node *, Node *);

    Node * cloneAutomata(Node *);

    void buildingBlockExp(char);
    void checkOperandValidity(string);
    void perfromOperation();

    int findDefinition (string);
    //used for expression/definition evaluation
    stack<Node*> operands;
    stack<char> operators;
};


#endif //LEXICAL_ANALYZER_LEXICALRULEPARSER_H
