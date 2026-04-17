#include "Polish_notation.hpp"
#include "utils.hpp"


// ========== ВЫЧИСЛЕНИЕ PN ==========
double evaluatePN(const string& expr) {
    Stack<double> values;
    Stack<char> ops;

    initStack(&values);
    initStack(&ops);

    cout << "=== ВЫЧИСЛЕНИЕ INFIX ===\n";

    for (size_t i = 0; i < expr.size(); i++) {

        // ПРОПУСК ПРОБЕЛОВ
        if (expr[i] == ' ') continue;

        // ЧИСЛО
        if (isdigit(expr[i]) || expr[i] == '.') {
			cout << "\n[Читаем число]: " << expr[i] << endl;
            string numStr;
            while (i < expr.size() && (isdigit(expr[i]) || expr[i] == '.')) {
                numStr += expr[i++];
            }
            i--;

            double num = stod(numStr);
            pushStack(&values, num);
            cout << "  Число: " << num << "\n";
        }

        // ПЕРЕМЕННАЯ
        else if (isVariable(expr[i])) {
            char var = expr[i];
			cout << "\n[Читаем переменную]: " << var << endl;
            if (variables.find(var) == variables.end()) {
                cout << "Введите значение для " << var << ": ";
                cin >> variables[var];
            }
            pushStack(&values, variables[var]);
        }

        // ОТКРЫВАЮЩАЯ СКОБКА
        else if (expr[i] == '(') {
			cout << "\n[Открывающая скобка]: " << expr[i] << endl;
            pushStack(&ops, expr[i]);
        }

        // ЗАКРЫВАЮЩАЯ СКОБКА
        else if (expr[i] == ')') {
			cout << "\n[Закрывающая скобка]: " << expr[i] << endl;
            while (ops.size > 0 && topStack(&ops) != '(') {
                double b = popStack(&values);
                double a = popStack(&values);
                char op = popStack(&ops);

                double res = applyOperator(a, b, op);
                pushStack(&values, res);
            }
            popStack(&ops); // убрать '('
        }

        // ОПЕРАТОР
        else if (isOperator(expr[i])) {
			cout << "\n[Оператор]: " << expr[i] << endl;
            while (ops.size > 0 &&
                getPriority(topStack(&ops)) >= getPriority(expr[i])) {

                double b = popStack(&values);
                double a = popStack(&values);
                char op = popStack(&ops);

                double res = applyOperator(a, b, op);
                pushStack(&values, res);

                cout << "  " << a << " " << op
                    << " " << b << " = " << res << "\n";
            }
            pushStack(&ops, expr[i]);
        }
    }

    // ДОСЧИТЫВАЕМ
    while (ops.size > 0) {
		cout << "\n[Остаток в стеке операторов]: " << topStack(&ops) << endl;
        double b = popStack(&values);
        double a = popStack(&values);
        char op = popStack(&ops);

        double res = applyOperator(a, b, op);
        pushStack(&values, res);
    }

    double result = popStack(&values);

    freeStack(&values);
    freeStack(&ops);

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
