#include "Polish_notation.hpp"
#include "utils.hpp";

// ========== ВЫЧИСЛЕНИЕ PN ==========
double evaluatePN(const string& pn) {
    Stack<double> st;
    initStack(&st);

    int len = pn.length();

    printf("\n=== ВЫЧИСЛЕНИЕ ПРЯМОЙ ПОЛЬСКОЙ НОТАЦИИ ===\n");

    for (int i = len - 1; i >= 0; i--) {
        if (pn[i] == ' ') continue;

        if (isdigit(pn[i])) {
            char numStr[64] = { 0 };
            int start = i;
            int pos = 0;

            while (i >= 0 && (isdigit(pn[i]) || pn[i] == '.')) i--;
            i++;

            for (int j = i; j <= start; j++) {
                numStr[pos++] = pn[j];
            }

            double num = atof(numStr);
            pushStack(&st, num);

            printf("  Помещаем %.2f в стек\n", num);
        }
        else if (isVariable(pn[i])) {
            if (variables.find(pn[i]) == variables.end()) {
                cout << "Введите значение для " << pn[i] << ": ";
                cin >> variables[pn[i]];
            }
            pushStack(&st, variables[pn[i]]);
        }
        else if (isOperator(pn[i])) {
            double a = popStack(&st);
            double b = popStack(&st);

            double result = applyOperator(a, b, pn[i]);

            pushStack(&st, result);

            printf("  %.2f %c %.2f = %.2f -> в стек\n",
                a, pn[i], b, result);
        }
    }

    double result = popStack(&st);
    freeStack(&st);
    return result;
}

// ========== ПРОВЕРКА ДЛЯ ПРЯМОЙ ПОЛЬСКОЙ НОТАЦИИ (ППН/PN) ==========
bool isValidPN(const string& s) {
    if (s.empty()) return false;

    // Проверка на допустимые символы
    string allowed = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ+-*/ ";
    for (size_t i = 0; i < s.length(); i++) {
        if (allowed.find(s[i]) == string::npos) {
            return false;
        }
    }

    int numCount = 0;
    int opCount = 0;

    for (size_t i = 0; i < s.length(); i++) {
        char c = s[i];

        if (c == ' ') continue;

        if (isDigit(c) || isVariable(c)) {
            // Пропускаем всё число
            while (i < s.length() && (isDigit(s[i]) || s[i] == '.')) {
                i++;
            }
            i--;
            numCount++;
        }
        else if (isOperator(c)) {
            opCount++;
        }
        else {
            return false;
        }
    }

    // В ППН: чисел должно быть на 1 больше, чем операторов
    if (numCount != opCount + 1) return false;
    if (numCount == 0) return false;

    return true;
}
