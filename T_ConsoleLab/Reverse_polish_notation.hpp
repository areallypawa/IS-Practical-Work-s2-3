#pragma once
#include <iostream>
#include <string>
#include "utils.hpp"
#include "Stack.hpp"
using namespace std;

string infixToRPN(const string& infix);
string RPNtoPN(const string& rpn);
double evaluateRPN(const string& rpn);
bool isValidRPN(const string& s);


