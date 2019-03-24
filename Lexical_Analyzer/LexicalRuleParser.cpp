//
// Created by alaa on 3/20/2019.
//

#include "LexicalRuleParser.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <regex>
#include <stack>
#include <vector>
#include <queue>
#include "Node.h"

using namespace std;

void LexicalRuleParser::readfile(string fileName) {
    string line;
    ifstream rulesFile(fileName);
    if (rulesFile.is_open())
    {
        while (getline(rulesFile,line))
        {
            findRuleType(line);
           // rules.push_back(line);
        }
        rulesFile.close();
    } else {
        cout << "file cannot be opened" << endl;
    }
}

void LexicalRuleParser::groupRules() {
    list<string>::iterator it;
    for (it = rules.begin(); it != rules.end(); ++it){
        string rule = it->c_str();
        LexicalRuleParser::findRuleType(rule);
    }
}

void LexicalRuleParser::findRuleType(string rule) {

    regex expressionRegex("\\s*[a-zA-Z]+\\s*:\\s*");
    regex definitionRegex("\\s*[a-zA-Z]+\\s*=\\s*");
    regex punctuationRegex("^\\[");
    regex keywordRegex("^\\{");

    if (regex_search(rule, punctuationRegex)) {
        punctuationList.push_back(rule);
    } else if (regex_search(rule, keywordRegex)) {
        keywordList.push_back(rule);
    } else if (regex_search(rule, expressionRegex)) {
        expressionList.push_back(rule);
    } else if (regex_search(rule, definitionRegex)) {
        definitionList.push_back(rule);
    } else {
        cout << "Error in input rule!" << endl;
    }

}

void LexicalRuleParser::parseRules() {

   // groupRules();
    nodesID = 0;
    createKeywordAutomata();
    createPuncAutomata();
    createDefinAutomata();
    createExpAutomata();

    combineNFA();

}

void LexicalRuleParser::createKeywordAutomata() {
    list<string>::iterator it;

    for (it = keywordList.begin(); it != keywordList.end(); ++it){
        string str = it->c_str();
        //split keywords and ignore the surrounding brackets
        vector<string> keywords = split(str.substr(1,str.size() - 2), ' ');
        buildKeywordAutomataGraph(keywords);
    }
}

void LexicalRuleParser::buildKeywordAutomataGraph(vector<string> keywords) {

    for (int i = 0; i < keywords.size(); i++) {
        int keySize = keywords[i].size();
        string current = keywords[i].c_str();

        Node* node;
        char input[2];
        input[1] = '\0';
        for (int c = 0; c < keySize; c++) {
            if (c == 0) {
                node = new Node(keywords[i], nodesID++);
            } else {
                node = node->getNext();
            }
            Node* nextNode = new Node(keywords[i], nodesID++);
            input[0] = current[c];
            node->addTransition(Transition(nextNode, input));
            automataNodes.push_back(node);
            grammarInput.insert(current[c]);
            if (c == 0) {
                automatas.push_back(node);
                node->setStartNode(true);
            }
        }
        node = node->getNext();
        node->setAcceptorNode(true);
    }
}

void LexicalRuleParser::createPuncAutomata() {
    list<string>::iterator it;
    for (it = punctuationList.begin(); it != punctuationList.end(); ++it){
        string str = it->c_str();
        vector<string> punct = split(str.substr(1,str.size() - 2), ' ');
        buildPunctAutomataGraph(punct);
    }
}

void LexicalRuleParser::buildPunctAutomataGraph(vector<string> punct) {
    char input[2];
    input[1] = '\0';
    for (int i = 0; i < punct.size(); i++) {
        string temp = (punct[i]).substr(punct[i].length() - 1, 1);
        Node* node = new Node(temp, nodesID++);
        node->setStartNode(true);
        Node* nextNode = new Node(temp, nodesID++);
        nextNode->setAcceptorNode(true);
        input[0] = temp[0];
        node->addTransition(Transition(nextNode, input));

        automatas.push_back(node);
        automataNodes.push_back(node);
        automataNodes.push_back(nextNode);
        grammarInput.insert(input[0]);
    }
}

void LexicalRuleParser::createExpAutomata() {
    list<string>::iterator it;
    for (it = expressionList.begin(); it != expressionList.end(); ++it){
        string str = it->c_str();
        string type = getDEtype(str);
        //take string after ':' part
        int startOfDef = str.find_first_of(':') + 1;
        str = str.substr(startOfDef, str.size() - startOfDef);
        int skipWhitespace = str.find_first_not_of(' ');

        buildDEAutomataGraph(str.substr(skipWhitespace, str.size() - skipWhitespace));

        Node * node = bfsEndNodeSearch(operands.top());
        node->setType(type);
        operands.top()->setType(type);
        automatas.push_back(operands.top());
    }
}

void LexicalRuleParser::createDefinAutomata() {
    list<string>::iterator it;
    for (it = definitionList.begin(); it != definitionList.end(); ++it){
        string str = it->c_str();
        string type = getDEtype(str);
        helpingNotations.push_back(type);
        //take string after '=' part
        int startOfDef = str.find_first_of('=') + 1;
        str = str.substr(startOfDef, str.size() - startOfDef);
        int skipWhitespace = str.find_first_not_of(' ');

        buildDEAutomataGraph(str.substr(skipWhitespace, str.size() - skipWhitespace));

        Node * node = bfsEndNodeSearch(operands.top());
        node->setType(type);
        operands.top()->setType(type);
        helpingAutomatas.push_back(operands.top());
    }
}

string LexicalRuleParser::getDEtype(string str) {
    regex rgx("^\\w+");
    smatch match;
    const string input = str;
    regex_search(input.begin(), input.end(), match, rgx);

    return match.str(0);
}

void LexicalRuleParser::buildDEAutomataGraph(string definition) {
    stack<char>().swap(operators);
    stack<Node *>().swap(operands);

    string operand;
    bool concatenate = false;
    int size = definition.size();
    for (int i = 0; i < definition.size(); i++) {
        char ch = definition[i];

        if (ch == '\\') {
            if (i-1 >= 0 && definition[i-1] == '\\') {
                buildSingleAlnum(ch);
            }
        } else if (ch == EPSILON[0] && i-1 >= 0&& definition[i - 1] == '\\') {
            concatenate = false;
            buildSingleAlnum(EPSILON[0]);
        } else if (isalpha(ch)) {
            concatenate = false;
            operand += ch;
        } else if (isdigit(ch)) {
            concatenate = false;
            operand = "";
            buildSingleAlnum(ch);
        } else if (isOperation(ch) && i-1 >=0 && definition[i-1] == '\\') {
            buildSingleAlnum(ch);
            if (concatenate) {
                precedenceOpHandler(' ');
            }
            concatenate = true;
        } else if (!isOperation(ch)) {
            buildSingleAlnum(ch);
            if (concatenate) {
                precedenceOpHandler(' ');
            }
            concatenate = true;
        } else if (ch == ' ') {
            concatenate = false;
            if (operand != "") {
                checkOperandValidity(operand);
                operand = "";
            }
            if (whiteSpaceIsOperator(i, definition)){
                precedenceOpHandler(ch);
            }
        } else {
            concatenate = false;
            if (operand != "") {
                checkOperandValidity(operand);
                operand = "";
            }
            if (ch == ')') {
                while (operators.top() != '(') {
                    perfromOperation();
                }
                operators.pop();
            } else if (ch == '(') {
                while (!operators.empty() && precedence(operators.top()) == 3) {
                    perfromOperation();
                }
                operators.push(ch);
            } else if (!operators.empty() && (precedence(operators.top()) > precedence(ch)
                    || precedence(operators.top()) == precedence(ch))) {
                precedenceOpHandler(ch);
            } else if (operators.empty() || precedence(operators.top()) < precedence(ch)) {
                operators.push(ch);
            }

        }
    }
    if (operand != "") {
        checkOperandValidity(operand);
        operand = "";
    }
    while(!operators.empty()) {
        perfromOperation();
    }
    if (operands.size() > 1) {
        operators.push(' ');
        perfromOperation();
    }
}

void LexicalRuleParser::precedenceOpHandler(char ch) {
    while (!operators.empty() && (precedence(operators.top()) > precedence(ch)
                                  || precedence(operators.top()) == precedence(ch))
           && operators.top() != '(') {
        perfromOperation();
        if (!operators.empty() && operators.top() == '(') {
            operators.pop();
        }
    }
    operators.push(ch);
}

Node* LexicalRuleParser::bfsEndNodeSearch(Node * start) {
    queue<Node *> q;
    q.push(start);

    while (!q.empty()) {
        Node* node = q.front();
        q.pop();
        if (node->isAcceptor()) {
            return node;
        }
        vector<Transition> trans = node->getTransition();
        for (int i = 0; i < trans.size(); i++) {
            q.push(trans[i].getNode());
        }
    }

    return nullptr;
}

void LexicalRuleParser::perfromOperation() {
    Node * node1 = operands.top();
    operands.pop();
    char op = operators.top();
    operators.pop();
    Node * node2;
    if (!operands.empty()) {
        node2 = operands.top();
    }
    if (op == ' ') {
        operands.pop();
        operands.push(concatenateExpression(node2, node1));
    } else if (op == '|') {
        operands.pop();
        operands.push(orExpression(node1, node2));
    } else if (op == '*') {
        operands.push(kleenClosureExp(node1));
    } else if (op == '+') {
        operands.push(positiveClosureExp(node1));
    } else if (op == '-') {
        operands.pop();
        operands.push(rangeExpression(node2, node1));
    }

}

Node * LexicalRuleParser::concatenateExpression(Node * node1, Node * node2) {
    Node * temp = bfsEndNodeSearch(node1);

    temp->setAcceptorNode(false);
    temp->addTransition(Transition(node2, EPSILON));
    node2->setStartNode(false);

    return node1;
}

Node * LexicalRuleParser::positiveClosureExp(Node * start) {

    visitedNodes.clear();
    newlyCreatedNodes.clear();

    Node * clonedNode = cloneAutomata(start);
    Node * node = kleenClosureExp(clonedNode);
    Node* n = concatenateExpression(start, node);
    return n;
}

Node * LexicalRuleParser::kleenClosureExp(Node * start) {

    Node * newStart = new Node(nodesID++);
    start->setStartNode(false);
    newStart->setStartNode(true);

    newStart->addTransition(Transition(start, EPSILON));

    Node * newEnd = new Node(nodesID++);
    newEnd->setAcceptorNode(true);

    Node * temp = bfsEndNodeSearch(start);;

    temp->setAcceptorNode(false);
    temp->addTransition(Transition(start, EPSILON));
    temp->addTransition(Transition(newEnd, EPSILON));
    newStart->addTransition(Transition(newEnd, EPSILON));

    return newStart;

}

Node* LexicalRuleParser::orExpression(Node * node1, Node * node2) {

    Node * newStart = new Node(nodesID++);
    node1->setStartNode(false);
    node2->setStartNode(false);
    newStart->setStartNode(true);

    newStart->addTransition(Transition(node1, EPSILON));
    newStart->addTransition(Transition(node2, EPSILON));

    Node * newEnd = new Node(nodesID++);
    newEnd->setAcceptorNode(true);

    //find end node
    Node * temp = bfsEndNodeSearch(node1);
    temp->addTransition(Transition(newEnd, EPSILON));
    temp->setAcceptorNode(false);

    //find end node
    temp = bfsEndNodeSearch(node2);
    temp->addTransition(Transition(newEnd, EPSILON));
    temp->setAcceptorNode(false);

    return newStart;
}

Node * LexicalRuleParser::rangeExpression(Node * node1, Node * node2) {
    Node * newStart = new Node (nodesID++);
    newStart->setStartNode(true);
    Node * newEnd = new Node (nodesID++);
    newEnd->setAcceptorNode(true);

    char* range;
    char* input1 = node1->getFirstTransition().getInput();
    char* input2 = node2->getFirstTransition().getInput();
    range = getRange(*input1, *input2);
    newStart->addTransition(Transition(newEnd, range));
    return newStart;
}


Node* LexicalRuleParser::cloneAutomata(Node * start) {

    Node * newNode = new Node (start->getType(), nodesID++);
    newNode->setAcceptorNode(start->isAcceptor());
    newNode->setStartNode(start->isStart());
    visitedNodes.push_back(start);
    newlyCreatedNodes.push_back(newNode);

    vector<Transition> trans = start->getTransition();
    for (int i = 0; i < trans.size(); i++) {
        Node * n;
        if ((n = isVisited(trans[i].getNode())) == nullptr) {
            n = cloneAutomata(trans[i].getNode());
        }
        char* input = new char[strlen(trans[i].getInput())+1];
        strcpy(input, trans[i].getInput());
        newNode->addTransition(Transition (n, input));
    }
    return newNode;
}

Node* LexicalRuleParser::isVisited(Node * node) {
    for (int i = 0; i < visitedNodes.size(); i++) {
        if (visitedNodes[i] == node){
            return newlyCreatedNodes[i];
        }
    }
    return nullptr;
}

void LexicalRuleParser::checkOperandValidity(string input) {
    int index = findDefinition(input);
    if (input.size() == 1 && isalpha(input[0])) {
        buildSingleAlnum(input[0]);
    } else if (input.size() > 1 && index >= 0) {
        visitedNodes.clear();
        newlyCreatedNodes.clear();
        operands.push(cloneAutomata(helpingAutomatas[index]));
    }
}

int LexicalRuleParser::findDefinition(string definitionName) {
    vector<string>::iterator it;

    it = find (helpingNotations.begin(), helpingNotations.end(), definitionName);
    if (it != helpingNotations.end())
        return  distance(helpingNotations.begin(), it);
    else
        return -1;
}

void LexicalRuleParser::buildSingleAlnum(char input) {
    char inputChar[2];
    inputChar[1] = '\0';
    Node* node = new Node(nodesID++);
    node->setStartNode(true);
    Node* nextNode = new Node(nodesID++);
    nextNode->setAcceptorNode(true);
    inputChar[0] = input;
    node->addTransition(Transition(nextNode, inputChar));
    operands.push(node);
    grammarInput.insert(input);
}

int LexicalRuleParser::precedence(char operation) {
    switch (operation) {
        case '*':
            return 3;
        case '+':
            return 3;
        case ' ':
            return 2;
        case '-':
            return 1;
        case '|':
            return 0;
        default:
            return -1;
    }
}

bool LexicalRuleParser::isOperation(char ch) {
    if (ch == '*' || ch == '+' || ch == '-' || ch == ' '
        || ch == '|' || ch == '(' || ch == ')') {
        return true;
    }
    return false;
}

bool LexicalRuleParser::whiteSpaceIsOperator(int i, string definition) {
    if (definition[i-1] == '(' || definition[i+1] == ')'
        || definition[i-1] == '|' || definition[i+1] == '|'
        || definition[i-1] == '-' || definition[i+1] == '-'
        || i+1 >= definition.size()) {
        return false;
    }
    return true;

}
char* LexicalRuleParser::getRange(char start, char end) {

    //size of char array = range + 1 for null terminator
        int charSize = end - start + 2;
        char *range = new char[charSize];

        int j = 0;
        for (int i = start; i < end; i++) {
            range[j++] = (char)i;
            grammarInput.insert(char(i));
        }
        range[j++] = (char)end;
        range[j] = '\0';

        return range;
}

vector<string> LexicalRuleParser::split(string str, char delimiter) {
    vector<string> internal;
    stringstream ss(str);
    string tok;

    while(getline(ss, tok, delimiter)) {
        if (tok == "") {
            continue;
        }
        internal.push_back(tok);
    }

    return internal;
}

void LexicalRuleParser::combineNFA() {
    Node* newNode = new Node(nodesID++);
    newNode->setStartNode(true);
    for (int i = 0; i < automatas.size(); i++) {
        automatas[i]->setStartNode(false);
        newNode->addTransition(Transition(automatas[i], EPSILON));
    }
    automataNodes.push_back(newNode);
    NFAstartNode = newNode;
}

Node* LexicalRuleParser::getNFAstartNode() {
    return NFAstartNode;
}

vector<Node *> LexicalRuleParser::getAllAutomataNodes() {
    return automataNodes;
}

vector<char> LexicalRuleParser::getAutomataInput() {
    return automataInputs;
}

vector<Node *> LexicalRuleParser::getAutotmatas() {
    return automatas;
}