#include "Reverse_polish_notation.hpp"
#include "utils.hpp"

double evaluateRPN(const string& rpn) {
    Stack<double> st;
    initStack(&st);

    cout << "=== ВЫЧИСЛЕНИЕ RPN ===\n";

    string token = "";

    for (size_t i = 0; i <= rpn.size(); i++) {
        if (i < rpn.size() && rpn[i] != ' ') {
            token += rpn[i];
        }
        else {
            if (!token.empty()) {

                // ЧИСЛО
                if (isdigit(token[0]) || token[0] == '.') {
                    double num = stod(token);
                    pushStack(&st, num);
                    cout << "  Помещаем " << num << " в стек\n";
                }
                else if (isVariable(token[0])) {
                    if (variables.find(token[0]) == variables.end()) {
                        cout << "Введите значение для " << token[0] << ": ";
                        cin >> variables[token[0]];
                    }
                    pushStack(&st, variables[token[0]]);
                }

                // ОПЕРАТОР
                else if (token.size() == 1 && isOperator(token[0])) {
                    double b = popStack(&st);
                    double a = popStack(&st);

                    double result = applyOperator(a, b, token[0]);

                    pushStack(&st, result);

                    cout << "  " << a << " " << token[0]
                        << " " << b << " = " << result << " -> в стек\n";
                }

                token = "";
            }
        }
    }

    double result = popStack(&st);
    freeStack(&st);
    return result;
}


string RPNtoPN(const string& rpn) {
    Stack<string> st;
    initStack(&st);

    string token = "";

    cout << "\n=== RPN -> PN ===\n";

    for (size_t i = 0; i <= rpn.size(); i++) {

        if (i < rpn.size() && rpn[i] != ' ') {
            token += rpn[i];
        }
        else {
            if (token.empty()) continue;

            cout << "\n[Токен]: " << token << endl;

            // ===== ОПЕРАТОР =====
            if (token.size() == 1 && isOperator(token[0])) {

                string b = popStack(&st);
                string a = popStack(&st);

                cout << "[ОПЕРАТОР]: " << token << endl;
                cout << "  pop a = " << a << endl;
                cout << "  pop b = " << b << endl;

                string expr = token + " " + a + " " + b;

                cout << "  склеиваем: " << expr << endl;
                cout << "  push в стек\n";

                pushStack(&st, expr);
            }

            // ===== ЧИСЛО / ОПЕРАНД =====
            else {
                cout << "[ЧИСЛО] push в стек: " << token << endl;
                pushStack(&st, token);
            }

            token = "";
        }
    }

    cout << "\n[ФИНАЛ] очистка стека\n";

    string result = popStack(&st);

    cout << "\n=== ГОТОВАЯ PN: " << result << "===" << endl;

    return result;
}


string infixToRPN(const string& infix) {
    Stack<char> operators;
    initStack(&operators);

    string rpn;

    cout << "\n=== INFIX -> RPN ===\n";

    for (size_t i = 0; i < infix.length(); i++) {
        char c = infix[i];
        if (c == ' ') continue;

        cout << "\n[Читаем]: " << c << endl;
        
        // ===== ЧИСЛО =====
        if (isdigit(c) || isVariable(c)) {
            cout << "[ОПЕРАНД] считываем: ";

            while (i < infix.length() &&
                (isdigit(infix[i]) || infix[i] == '.' || isVariable(infix[i]))) {
                cout << infix[i];
                rpn += infix[i];
                i++;
            }

            rpn += ' ';
            cout << " -> добавлено в RPN\n";

            i--;
        }

        // ===== ( =====
        else if (c == '(') {
            cout << "[СТЕК] push '(' в стек операторов\n";
            pushStack(&operators, c);
        }

        // ===== ) =====
        else if (c == ')') {
            cout << "[СТЕК] обработка ')'\n";

            while (!isEmptyStack(&operators) && topStack(&operators) != '(') {
                char op = popStack(&operators);
                cout << "[POP] " << op << " -> в RPN\n";

                rpn += op;
                rpn += ' ';
            }

            if (!isEmptyStack(&operators)) {
                cout << "[POP] удаляем '('\n";
                popStack(&operators);
            }
        }

        // ===== ОПЕРАТОР =====
        else if (isOperator(c)) {
            cout << "[ОПЕРАТОР] " << c << " -> работа со стеком\n";

            while (!isEmptyStack(&operators) &&
                topStack(&operators) != '(' &&
                getPriority(topStack(&operators)) >= getPriority(c)) {

                char op = popStack(&operators);
                cout << "[POP] " << op << " (приоритет) -> RPN\n";

                rpn += op;
                rpn += ' ';
            }

            pushStack(&operators, c);
            cout << "[PUSH] " << c << " в стек\n";
        }
    }

    // ===== ОЧИСТКА СТЕКА =====
    cout << "\n[ФИНАЛ] очистка стека\n";

    while (!isEmptyStack(&operators)) {
        char op = popStack(&operators);
        cout << "[POP] " << op << " -> RPN\n";

        rpn += op;
        rpn += ' ';
    }

    freeStack(&operators);

    cout << "\n=== ГОТОВЫЙ RPN: " << rpn << "===\n";

    return rpn;
}


bool isValidRPN(const string& s) {
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
    bool lastWasNumber = false;
    bool lastWasOperator = false;

    for (size_t i = 0; i < s.length(); i++) {
        char c = s[i];

        if (c == ' ') {
            lastWasNumber = false;
            lastWasOperator = false;
            continue;
        }

        if (isDigit(c) || isVariable(c)) {
			
            // Пропускаем всё число
            while (i < s.length() && (isDigit(s[i]) || s[i] == '.')) {
                i++;
            }
            
            numCount++;
            lastWasNumber = true;
            lastWasOperator = false;
        }
        else if (isOperator(c)) {
            opCount++;
            lastWasNumber = false;
            lastWasOperator = true;
        }
        else {
            return false;
        }
    }

    // В ОПН: чисел должно быть на 1 больше, чем операторов
    if (numCount != opCount + 1) return false;
    if (numCount == 0) return false;
    if (lastWasOperator == false && numCount > 1) return false;

    return true;
}