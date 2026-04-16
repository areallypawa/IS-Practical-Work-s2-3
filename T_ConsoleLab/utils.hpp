#pragma once
#include <string>
using namespace std;

int getPriority(char op);
int isOperator(char c);
double applyOperator(double a, double b, char op);
bool isDigit(char p);

bool isValidExpression(const string& s);
