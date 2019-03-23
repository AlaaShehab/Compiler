#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <regex>
#include "Node.h"
#include "Transition.h"

using namespace std;

int nodesID = 0;
vector<Node *> automatas;
vector<string> split(string str, char delimiter);
void buildKeywordAutomataGraph(vector<string> keywords);
char* getRange(char start, char end);
int main() {

    char* range;
    range = getRange('a', 'd');
    cout << range << endl;
    return 0;
}

char* getRange(char start, char end) {
    int charSize = end - start + 2;

    char *range = new char[charSize];
    int j = 0;
    for (int i = start; i < end; i++) {

        range[j++] = (char)i;
    }
    range[j++] = end;
    range[j] = '\0';

    return range;
}

vector<string> split(string str, char delimiter) {
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

void buildKeywordAutomataGraph(vector<string> keywords) {
    for (int i = 0; i < keywords.size(); i++) {
        int keySize = keywords[i].size();
        string current = keywords[i].c_str();

        Node* node;
        for (int c = 0; c < keySize; c++) {
            if (c == 0) {
                node = new Node(keywords[i], nodesID++);
            } else {
                node = node->getNext();
            }

            Node* nextNode = new Node(keywords[i], nodesID++);
            char input = current[c];

            cout << current[c] << endl;
            node->addTransition(Transition(nextNode, &input));
            if (c == 0) {
                automatas.push_back(node);
                node->setStartNode(true);
            }
        }
        node = node->getNext();
        node->setAcceptorNode(true);
    }
}