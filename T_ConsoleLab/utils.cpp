#include "utils.hpp";

std::map<char, double> variables;

int getPriority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

double applyOperator(double a, double b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
    default: return 0;
    }
}

bool isDigit(char p) {
    return (p >= '0' && p <= '9');
}

bool isVariable(char c) {
    return isalpha(c); // a, b, x, y...
}

bool isValidExpression(const string& s) {
    if (s.empty()) return false;

    string allowed = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ+-*/ ";
    for (size_t i = 0; i < s.length(); i++) {
        if (allowed.find(s[i]) == string::npos) {
            return false;
        }
    }

    string expr;
    for (size_t i = 0; i < s.length(); i++) {
        if (s[i] != ' ') expr += s[i];
    }

    if (expr.empty()) return false;

    int balance = 0;
    bool lastWasOperator = true;
    int numCount = 0;
    int opCount = 0;

    for (size_t i = 0; i < expr.length(); i++) {
        char c = expr[i];

        if (isDigit(c) || isVariable(c)) {
            if (i == 0 || !isDigit(expr[i - 1])) {
                numCount++;
            }
            lastWasOperator = false;
        }
        else if (c == '(') {
            balance++;
            lastWasOperator = true;
        }
        else if (c == ')') {
            if (lastWasOperator) return false;
            balance--;
            if (balance < 0) return false;
            lastWasOperator = false;
        }
        else if (isOperator(c)) {
            if (lastWasOperator) return false;
            lastWasOperator = true;
            opCount++;
        }
    }

    if (balance != 0) return false;
    if (lastWasOperator) return false;
    if (numCount == 0) return false;

    bool prevWasAny = false;
    char prevType = 0;

    for (size_t i = 0; i < expr.length(); i++) {
        char c = expr[i];

        if (isDigit(c)) {
            if (i > 0 && !isDigit(expr[i - 1]) && prevType == 'd') {
                return false;
            }
            prevType = 'd';
        }
        else if (c == '(') {
            prevType = '(';
        }
        else if (c == ')') {
            prevType = ')';
        }
        else if (isOperator(c)) {
            prevType = 'o';
        }
    }

    return true;
}