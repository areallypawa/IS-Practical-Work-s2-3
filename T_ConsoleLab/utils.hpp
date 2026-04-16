#pragma once
#include <string>
#include <map>
using namespace std;

extern map<char, double> variables;

int getPriority(char op);
int isOperator(char c);
double applyOperator(double a, double b, char op);
bool isDigit(char p);
bool isVariable(char c);
bool isValidExpression(const string& s);
