//
// Created by alaa on 4/16/2019.
//

#include "Production.h"
#include <string>
#include "vector"

using namespace std;

void Production::addStringToProduction(string productionComponent) {
    strings.push_back(productionComponent);
}

string Production::getStringAt(int index) {
    return strings[index];
}

vector<string> Production::getStrings() {
    return strings;
}