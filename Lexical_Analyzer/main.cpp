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
int main() {

    string str = "{ if then else while }";
    vector<string> keywords = split(str.substr(1,str.size() - 2), ' ');

    buildKeywordAutomataGraph(keywords);


    for (int i = 0; i < automatas.size(); i++) {

        cout << "start new automata " << endl;
        Node* node = automatas[i];
        char input;
        node->getFirstTransition().getInput(&input);

        cout << node->getName() << "  " << input  << node->isStart() << endl;

        node->getFirstTransition().getInput(&input);
        int name = node->getNext()->getName();


    }


    return 0;
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