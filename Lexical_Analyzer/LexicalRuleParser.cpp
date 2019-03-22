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
#include "Node.h"

using namespace std;

void LexicalRuleParser::readfile(string fileName) {
    string line;
    ifstream rulesFile(fileName);
    if (rulesFile.is_open())
    {
        while (getline(rulesFile,line))
        {
            rules.push_back(line);
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

    nodesID = 0;
    createKeywordAutomata();
    createPuncAutomata();
    createExpAutomata();
    createDefinAutomata();
}

void LexicalRuleParser::createKeywordAutomata() {
    list<string>::iterator it;

    for (it = keywordList.begin(); it != keywordList.end(); ++it){
        string str = it->c_str();
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
            automataInputs.push_back(current[c]);
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
        Node* node = new Node(punct[i], nodesID++);
        node->setStartNode(true);
        Node* nextNode = new Node(punct[i], nodesID++);
        nextNode->setAcceptorNode(true);
        input[0] = (punct[i])[0];
        node->addTransition(Transition(nextNode, input));
    }
}

void LexicalRuleParser::createExpAutomata() {

}

void LexicalRuleParser::createDefinAutomata() {
    //TODO can be minimized by making one method for both this and expression
    list<string>::iterator it;
    for (it = definitionList.begin(); it != definitionList.end(); ++it){
        string str = it->c_str();
        getDefinitionNotation(str);
        //take string after '=' part
        int startOfDef = str.find_first_of('=') + 1;
        str = str.substr(startOfDef, str.size() - startOfDef);
        int skipWhitespace = str.find_first_not_of(' ');

        buildDefinAutomataGraph(str.substr(skipWhitespace, str.size() - skipWhitespace));
    }
}

void LexicalRuleParser::getDefinitionNotation(string str) {
    regex rgx("^\\w+");
    smatch match;
    const string input = str;
    regex_search(input.begin(), input.end(), match, rgx);
    helpingNotations.push_back(match.str(0));
}

void LexicalRuleParser::buildDefinAutomataGraph(string definition) {
    stack<char>().swap(operators);
    stack<Node *>().swap(operands);

    string operand;
    for (int i = 0; i < definition.size(); i++) {
        char ch = definition[i];

        if (isalpha(ch)) {
            operand += ch;
        } else if (isdigit(ch)) {
            operand = "";
            buildingBlockExp(ch);
        } else if (ch == ' ') {
            if (operand != "") {
                checkOperandValidity(operand);
                operand = "";
            }
            if ((isalnum(definition[i-1]) && !isalnum(definition[i+1]))
                    || (isalnum((definition[i-1])) && definition[i+1] == '(')
                    || (definition[i-1] == ')') && isalnum((definition[i+1]))){
                operators.push(' ');
            }
        } else {
            if (operand != "") {
                checkOperandValidity(operand);
                operand = "";
            }
            if (ch == ')') {
                while (operators.top() != '(') {
                    perfromOperation();
                }
                operators.pop();
            } else if (precedence(operators.top()) > precedence(ch)
                    || precedence(operators.top()) == precedence(ch)) {
                while (precedence(operators.top()) > precedence(ch)
                       || precedence(operators.top()) == precedence(ch)) {
                    perfromOperation();
                }
                operators.push(ch);
            } else if (precedence(operators.top()) < precedence(ch)) {
                operators.push(ch);
            }

        }
    }

    if (operands.size() > 1) {
        Node * node2 = operands.top();
        operands.pop();
        Node * node1 = operands.top();
        operands.pop();
        operands.push(concatenateExpression(node1, node2));
    }

    Node * node = operands.top();
    while (!(node->isAcceptor())) {
        node = node->getNext();
    }
    string type = helpingNotations[helpingNotations.size() - 1];
    node->setType(type);
    operands.top()->setType(type);
    helpingAutomatas.push_back(operands.top());
}

void LexicalRuleParser::perfromOperation() {
    Node * node1 = operands.top();
    operands.pop();
    char op = operators.top();
    operators.pop();
    Node * node2 = operands.top();
    if (op == ' ') {
        operands.pop();
        concatenateExpression(node2, node1);
    } else if (op == '|') {
        orExpression(node1, node2);
        operands.pop();
    } else if (op == '*') {
        kleenClosureExp(node1);
    } else if (op == '+') {
        positiveClosureExp(node1);
    } else if (op == '-') {
        rangeExpression(node2, node1);
        operands.pop();
    }

}

Node * LexicalRuleParser::concatenateExpression(Node * node1, Node * node2) {
    char *ep;
    ep = &EPSILON;

    Node * temp = node1;
    while (!(temp->isAcceptor())) {
        temp = temp->getNext();
    }
    temp->setAcceptorNode(false);
    temp->addTransition(Transition(node2, ep));
    node2->setStartNode(false);

    return node1;
}

Node * LexicalRuleParser::positiveClosureExp(Node * start) {

    Node * node = cloneAutomata(start);
    node = kleenClosureExp(node);
    concatenateExpression(start, node);
}

Node* LexicalRuleParser::cloneAutomata(Node * start) {
    Node * newNode = new Node (start->getType(), nodesID++);
    vector<Transition> trans = start->getTransition();
    for (int i = 0; i < trans.size(); i++) {
        Node * n = cloneAutomata(trans[i].getNode());
        char* input = new char[strlen(trans[i].getInput())+1];
        strcpy(input, trans[i].getInput());
        Transition* t = new Transition (n, input);
    }
    return newNode;
}

Node * LexicalRuleParser::kleenClosureExp(Node * start) {
    char *ep;
    ep = &EPSILON;
    Node * newStart = new Node(nodesID++);
    start->setStartNode(false);
    newStart->setStartNode(true);

    newStart->addTransition(Transition(start, ep));

    Node * newEnd = new Node(nodesID++);
    newEnd->setAcceptorNode(true);

    Node * temp = start;
    while (!(temp->isAcceptor())) {
        temp = temp->getNext();
    }
    temp->setAcceptorNode(false);
    temp->addTransition(Transition(start, ep));
    temp->addTransition(Transition(newEnd, ep));
    newStart->addTransition(Transition(newEnd, ep));

    return newStart;

}

Node* LexicalRuleParser::orExpression(Node * node1, Node * node2) {
    char *ep;
    ep = &EPSILON;

    Node * newStart = new Node(nodesID++);
    node1->setStartNode(false);
    node2->setStartNode(false);
    newStart->setStartNode(true);

    newStart->addTransition(Transition(node1, ep));
    newStart->addTransition(Transition(node2, ep));

    Node * newEnd = new Node(nodesID++);
    newEnd->setAcceptorNode(true);
    Node * temp = node1;
    while (!(temp->isAcceptor())) {
        temp = temp->getNext();
    }
    temp->addTransition(Transition(newEnd, ep));
    temp->setAcceptorNode(false);

    temp = node2;
    while (!(temp->isAcceptor())) {
        temp = temp->getNext();
    }
    temp->addTransition(Transition(newEnd, ep));
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

void LexicalRuleParser::checkOperandValidity(string input) {
    int index = findDefinition(input);
    if (input.size() == 1 && isalpha(input[0])) {
        buildingBlockExp(input[0]);
    } else if (input.size() > 1 && index >= 0) {
        operands.push(helpingAutomatas[index]);
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

void LexicalRuleParser::buildingBlockExp(char input) {
    char inputChar[2];
    inputChar[1] = '\0';
    Node* node = new Node(nodesID++);
    node->setStartNode(true);
    Node* nextNode = new Node(nodesID++);
    nextNode->setAcceptorNode(true);
    inputChar[0] = input;
    node->addTransition(Transition(nextNode, inputChar));
    operands.push(node);
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

char* LexicalRuleParser::getRange(char start, char end) {

    //size of char array = range + 1 for null terminator
        int charSize = end - start + 2;
        char *range = new char[charSize];

        int j = 0;
        for (int i = start; i < end; i++) {

            range[j++] = (char)i;
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

vector<Node *> LexicalRuleParser::getAllAutomataNodes() {
    return automataNodes;
}

vector<char> LexicalRuleParser::getAutomataInput() {
    return automataInputs;
}

vector<Node *> LexicalRuleParser::getAutotmatas() {
    return automatas;
}