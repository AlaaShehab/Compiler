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
    //there's a problem in input as char * and problem in id value
    for (int i = 0; i < keywords.size(); i++) {
        int keySize = keywords[i].size();
        string current = keywords[i].c_str();

        Node node = Node(nodesID);
        for (int c = 0; c < keySize; c++) {
            if (c == 0) {
                node = Node(keywords[i], nodesID++);
            } else {
                node = node.getNext();
            }
            Node nextNode = Node(keywords[i], nodesID++);
            char input = current[c];
            node.addTransition(Transition(&nextNode, &input));
            automataNodes.push_back(node);
            automataInputs.push_back(current[c]);
            if (c == 0) {
                automatas.push_back(node);
                node.setStartNode(true);
            } else if (c == keySize - 1) {
                node.setAcceptorNode(true);
            }

        }
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
    for (int i = 0; i < punct.size(); i++) {
        Node node = Node(punct[i], nodesID++);
        node.setStartNode(true);
        Node nextNode = Node(punct[i], nodesID++);
        nextNode.setAcceptorNode(true);
        char input = (punct[i])[0];
        node.addTransition(Transition(&nextNode, &input));
    }
}

void LexicalRuleParser::createExpAutomata() {

}

void LexicalRuleParser::createDefinAutomata() {

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

vector<Node> LexicalRuleParser::getAllAutomataNodes() {
    return automataNodes;
}

vector<char> LexicalRuleParser::getAutomataInput() {
    return automataInputs;
}

vector<Node> LexicalRuleParser::getAutotmatas() {
    return automatas;
}