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


DFANode * generateNode () {
    int id = 0;
    DFANode* start = new DFANode("start", id++);
    start->setStartNode(true);

    DFANode* num = new DFANode("num", id++);
    num->setAcceptorNode(true);
    num->setTypeAccepted("num");

    DFANode* i_key = new DFANode("", id++);
    i_key->setAcceptorNode(true);
    i_key->setTypeAccepted("id");
    DFANode* id_ = new DFANode("id", id++);
    id_->setAcceptorNode(true);
    id_->setTypeAccepted("id");
    DFANode* W_key = new DFANode("while", id++);
    W_key->setAcceptorNode(true);
    W_key->setTypeAccepted("id");
    DFANode* mul = new DFANode("mulop", id++);
    mul->setAcceptorNode(true);
    mul->setTypeAccepted("mulop");
    DFANode* add = new DFANode("addop", id++);
    add->setAcceptorNode(true);
    add->setTypeAccepted("addop");
    DFANode* equal = new DFANode("", id++);
    equal->setAcceptorNode(true);
    equal->setTypeAccepted("assign");
    DFANode* great = new DFANode("relop", id++);
    great->setAcceptorNode(true);
    great->setTypeAccepted("relop");
    DFANode* notNode = new DFANode("", id++);


    char numbers[] = {'0','1','2','3','4','5','6','7','8','9','\0'};
    char i[] = {'i','\0'};
    char w[] = {'w','\0'};
    char mulOp[] = {'*','\0'};
    char addOp[] = {'+','\0'};
    char eqOp[] = {'=','\0'};
    char grOp[] = {'>','\0'};
    char notOp[] = {'!','\0'};

    set<char> letrs;
    for (int i = 0; i < 10; i++) {
        letrs.insert(char (i + 48));
    }
    for (int i = 0; i < 26; i++) {
        letrs.insert(char (i + 65));
        letrs.insert(char (i + 97));
    }

    letrs.erase('i');
    letrs.erase('w');

    vector<char> v(letrs.begin(), letrs.end());
    char* lettersIW = &v[0];

    start->addTransition(Transition(num, numbers));
    start->addTransition(Transition(i_key, i));
    start->addTransition(Transition(id_, lettersIW));
    start->addTransition(Transition(W_key, w));
    start->addTransition(Transition(mul, mulOp));
    start->addTransition(Transition(add, addOp));
    start->addTransition(Transition(equal, eqOp));
    start->addTransition(Transition(great, grOp));
    start->addTransition(Transition(notNode, notOp));

    //equal
    DFANode* equalequal = new DFANode("relop", id++);
    num->setAcceptorNode(true);
    num->setTypeAccepted("relop");
    char eeOp[] = {'=','\0'};
    equal->addTransition(Transition(equalequal, eeOp));

    //not equal
    DFANode* notequal = new DFANode("relop", id++);
    notequal->setAcceptorNode(true);
    notequal->setTypeAccepted("relop");
    notNode->addTransition(Transition(notequal, eqOp));

    //great
    DFANode* greatequal = new DFANode("relop", id++);
    num->setAcceptorNode(true);
    num->setTypeAccepted("relop");
    great->addTransition(Transition(greatequal, eqOp));

    //id
    letrs.insert('i');
    letrs.insert('w');

    vector<char> ve(letrs.begin(), letrs.end());
    char* letters = &ve[0];
    id_->addTransition(Transition(id_, letters));

    //int / if
    DFANode* if_key = new DFANode("if", id++);
    if_key->setAcceptorNode(true);
    if_key->setTypeAccepted("if");
    if_key->setTypeAccepted("id");
    DFANode* n_key = new DFANode("", id++);
    n_key->setAcceptorNode(true);
    n_key->setTypeAccepted("id");
    DFANode* t_key = new DFANode("int", id++);
    t_key->setAcceptorNode(true);
    t_key->setTypeAccepted("int");
    t_key->setTypeAccepted("id");
    char f[] = {'f','\0'};
    char n[] = {'n','\0'};
    char t[] = {'t','\0'};

    letrs.erase('f');
    letrs.erase('n');
    vector<char> vec(letrs.begin(), letrs.end());
    char* letterFN = &vec[0];

    letrs.insert('f');
    letrs.insert('n');
    letrs.erase('t');
    vector<char> vect(letrs.begin(), letrs.end());
    char* letterT = &vect[0];

    i_key->addTransition(Transition(if_key, f));
    i_key->addTransition(Transition(n_key, n));
    i_key->addTransition(Transition(id_, letterFN));

    if_key->addTransition(Transition(id_, letters));

    n_key->addTransition(Transition(t_key, t));
    n_key->addTransition(Transition(id_, letterT));

    t_key->addTransition(Transition(id_, letters));
    letrs.insert('t');

    //while
    DFANode* hNode = new DFANode("num", id++);
    hNode->setAcceptorNode(true);
    hNode->setTypeAccepted("id");
    DFANode* iNode = new DFANode("num", id++);
    iNode->setAcceptorNode(true);
    iNode->setTypeAccepted("id");
    DFANode* lNode = new DFANode("num", id++);
    lNode->setAcceptorNode(true);
    lNode->setTypeAccepted("id");
    DFANode* eNode = new DFANode("num", id++);
    eNode->setAcceptorNode(true);
    eNode->setTypeAccepted("while");
    eNode->setTypeAccepted("id");

    char h[] = {'h', '\0'};
    char l[] = {'l', '\0'};
    char e[] = {'e', '\0'};

    letrs.erase('h');
    vector<char> vecto(letrs.begin(), letrs.end());
    char* letterN = &vecto[0];
    letrs.insert('h');
    W_key->addTransition(Transition(hNode, h));
    W_key->addTransition(Transition(id_, letterN));

    letrs.erase('i');
    vector<char> vectorv(letrs.begin(), letrs.end());
    char* letterI = &vectorv[0];
    letrs.insert('i');
    hNode->addTransition(Transition(iNode, i));
    hNode->addTransition(Transition(id_, letterI));

    letrs.erase('l');
    vector<char> vectorve(letrs.begin(), letrs.end());
    char* letterL = &vectorve[0];
    letrs.insert('l');
    iNode->addTransition(Transition(lNode, l));
    iNode->addTransition(Transition(id_, letterL));

    letrs.erase('e');
    vector<char> vectorvec(letrs.begin(), letrs.end());
    char* letterE = &vectorvec[0];
    letrs.insert('e');
    lNode->addTransition(Transition(eNode, e));
    lNode->addTransition(Transition(id_, letterL));

    eNode->addTransition(Transition(id_, letters));


    //num
    DFANode* dotN = new DFANode("num", id++);
    DFANode* afterDotN = new DFANode("num", id++);
    afterDotN->setAcceptorNode(true);
    afterDotN->setTypeAccepted("num");
    DFANode* eN = new DFANode("num", id++);
    DFANode* endN = new DFANode("num", id++);
    endN->setAcceptorNode(true);
    endN->setTypeAccepted("num");

    char dot[] = {'.','\0'};
    char E[] = {'E','\0'};
    num->addTransition(Transition(num, numbers));
    num->addTransition(Transition(dotN, dot));

    dotN->addTransition(Transition(afterDotN, numbers));

    afterDotN->addTransition(Transition(afterDotN, numbers));
    afterDotN->addTransition(Transition(eN, E));

    eN->addTransition(Transition(endN, numbers));

    endN->addTransition(Transition(endN, numbers));

    //punctuation
    DFANode* n1 = new DFANode(",", id++);
    n1->setAcceptorNode(true);
    n1->setTypeAccepted(",");
    DFANode* n2 = new DFANode(";", id++);
    n2->setAcceptorNode(true);
    n2->setTypeAccepted(";");
    DFANode* n3 = new DFANode("(", id++);
    n3->setAcceptorNode(true);
    n3->setTypeAccepted("(");
    DFANode* n4 = new DFANode(")", id++);
    n4->setAcceptorNode(true);
    n4->setTypeAccepted(")");
    DFANode* n5 = new DFANode("}", id++);
    n5->setAcceptorNode(true);
    n5->setTypeAccepted("}");
    DFANode* n6 = new DFANode("{", id);
    n6->setAcceptorNode(true);
    n6->setTypeAccepted("{");

    char n1Op[] = {',', '\0'};
    char n2Op[] = {';', '\0'};
    char n3Op[] = {'(', '\0'};
    char n4Op[] = {')', '\0'};
    char n5Op[] = {'}', '\0'};
    char n6Op[] = {'{', '\0'};

    start->addTransition(Transition(n1, n1Op));
    start->addTransition(Transition(n2, n2Op));
    start->addTransition(Transition(n3, n3Op));
    start->addTransition(Transition(n4, n4Op));
    start->addTransition(Transition(n5, n5Op));
    start->addTransition(Transition(n6, n6Op));



    return start;

}
int main() {

    LexicalRuleParser dfa;
    dfa.readfile("D:\\Projects\\Compiler\\Lexical_Analyzer\\example.txt");
    dfa.parseRules();
    map<string, int> map = dfa.getPriority();

    DFANode * node = generateNode();
    TokenGenerator generator = TokenGenerator(node, map);
    generator.tokenizeCode("D:\\Projects\\Compiler\\Lexical_Analyzer\\program.txt");





    return 0;
}


