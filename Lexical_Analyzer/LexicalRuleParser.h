//
// Created by alaa on 3/20/2019.
//

#ifndef LEXICAL_ANALYZER_LEXICALRULEPARSER_H
#define LEXICAL_ANALYZER_LEXICALRULEPARSER_H
#include <string>
#include "Node.h"
#include <stack>
#include <vector>
#include <set>

using namespace std;

class LexicalRuleParser {
public:
    void readfile (string);
    void parseRules();
    //return char array of input that is sent as parameter
    vector<char> getAutomataInput ();
    vector<Node*> getAutotmatas ();
    vector<Node*> getAllAutomataNodes ();

<<<<<<< HEAD
    //static const string LAMDA = "\L";
    char EPSILON[2] = "\L";
=======
    Node* getNFAstartNode();
    char EPSILON[2] = "~";
>>>>>>> parsingTxtFile


private:


    //for cloning purpose
    vector<Node*> visitedNodes;
    vector<Node*> newlyCreatedNodes;

    //used to identify when a node will be added
    bool isExpression = false;

    //just to make sure that no input is repeated
    set<char> grammarInput;

    int nodesID;
    list<string> rules;

    Node* NFAstartNode;

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

    void combineNFA();

    void addNodes(Node *);
    void dfs(Node *);
    void adjustNodesPosition();

    void buildKeywordAutomataGraph(vector<string>);
    void buildPunctAutomataGraph(vector<string>);
    void buildDEAutomataGraph(string);

    vector<string> split(string, char);

    //TODO don't forget to remove duplicates from input
    //TODO don't forget to add all nodes at the end\
    // TODO make automata Input a set
    //TODO edit epsilon
    vector<Node*> automataNodes;
    vector<Node*> automatas;
    /*
     * used with definitions that are just helping | building parts of
     * regular expressions|definitions
    */
    vector<string> helpingNotations;
    vector<Node *> helpingAutomatas;

    /*
     * add name of a definition to list for later use
     */
    string getDEtype(string);


    int precedence (char);
    char* getRange(char, char);


    Node * concatenateExpression(Node *, Node *);
    Node * orExpression(Node *, Node *);
    Node * positiveClosureExp(Node *);
    Node * kleenClosureExp(Node *);
    Node * rangeExpression(Node *, Node *);

    Node * cloneAutomata(Node *);

<<<<<<< HEAD
=======
    Node * bfsEndNodeSearch(Node *);
>>>>>>> parsingTxtFile
    void buildSingleAlnum(char);
    void checkOperandValidity(string);
    void perfromOperation();

    Node * bfsEndNodeSearch(Node *);

    bool isOperation (char);
    int findDefinition (string);
<<<<<<< HEAD
    bool whiteSpaceIsOperator(int, string);

    void precedenceOpHandler(char);
=======
    bool isOperation(char);
    void precedenceOpHandler(char);

    Node * isVisited(Node *);
    bool whiteSpaceIsOperator(int, string);
>>>>>>> parsingTxtFile
    //used for expression/definition evaluation
    stack<Node*> operands;
    stack<char> operators;

    bool isDigit(char);
};


#endif //LEXICAL_ANALYZER_LEXICALRULEPARSER_H
