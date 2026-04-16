#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cctype>
#include <cmath>

using namespace std;

// ========== СТРУКТУРЫ ==========
typedef struct {
    double* data;
    int size;
    int capacity;
} Stack;

typedef struct {
    char** data;
    int size;
    int capacity;
} Array;

// ========== ФУНКЦИИ ДЛЯ СТЕКА ==========
void initStack(Stack* s) {
    s->capacity = 10;
    s->size = 0;
    s->data = (double*)malloc(s->capacity * sizeof(double));
}

void pushStack(Stack* s, double value) {
    if (s->size >= s->capacity) {
        s->capacity *= 2;
        s->data = (double*)realloc(s->data, s->capacity * sizeof(double));
    }
    s->data[s->size++] = value;
}

double popStack(Stack* s) {
    if (s->size == 0) return 0;
    return s->data[--s->size];
}

double topStack(Stack* s) {
    if (s->size == 0) return 0;
    return s->data[s->size - 1];
}

int isEmptyStack(Stack* s) {
    return s->size == 0;
}

void freeStack(Stack* s) {
    free(s->data);
    s->data = NULL;
    s->size = 0;
    s->capacity = 0;
}

// ========== ФУНКЦИИ ДЛЯ ДИНАМИЧЕСКОГО МАССИВА ==========
void initArray(Array* a) {
    a->capacity = 10;
    a->size = 0;
    a->data = (char**)malloc(a->capacity * sizeof(char*));
}

void addToArray(Array* a, const char* value) {
    if (a->size >= a->capacity) {
        a->capacity *= 2;
        a->data = (char**)realloc(a->data, a->capacity * sizeof(char*));
    }
    a->data[a->size] = (char*)malloc((strlen(value) + 1) * sizeof(char));
    strcpy(a->data[a->size], value);
    a->size++;
}

char* getFromArray(Array* a, int index) {
    if (index < 0 || index >= a->size) return NULL;
    return a->data[index];
}

void freeArray(Array* a) {
    for (int i = 0; i < a->size; i++) {
        free(a->data[i]);
    }
    free(a->data);
    a->data = NULL;
    a->size = 0;
    a->capacity = 0;
}

// ========== ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ==========
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

bool isValidExpression(const string& s) {
    if (s.empty()) return false;

    string allowed = "0123456789+-*/() ";
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

        if (isDigit(c)) {
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

// ========== ПРОВЕРКА ДЛЯ ОБРАТНОЙ ПОЛЬСКОЙ НОТАЦИИ (ОПН/RPN) ==========
bool isValidRPN(const string& s) {
    if (s.empty()) return false;

    // Проверка на допустимые символы
    string allowed = "0123456789+-*/ ";
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

        if (isDigit(c)) {
            // Пропускаем всё число
            while (i < s.length() && (isDigit(s[i]) || s[i] == '.')) {
                i++;
            }
            i--;
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

// ========== ПРОВЕРКА ДЛЯ ПРЯМОЙ ПОЛЬСКОЙ НОТАЦИИ (ППН/PN) ==========
bool isValidPN(const string& s) {
    if (s.empty()) return false;

    // Проверка на допустимые символы
    string allowed = "0123456789+-*/ ";
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

        if (isDigit(c)) {
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

// ========== ПРЕОБРАЗОВАНИЕ INFIX -> RPN ==========
void infixToRPN(const char* infix, Array* output) {
    Stack operators;
    initStack(&operators);
    int len = strlen(infix);

    printf("\n=== ПРЕОБРАЗОВАНИЕ INFIX -> RPN ===\n");

    for (int i = 0; i < len; i++) {
        char c = infix[i];
        if (c == ' ') continue;

        if (isdigit(c)) {
            char number[64] = { 0 };
            int pos = 0;
            while (i < len && (isdigit(infix[i]) || infix[i] == '.')) {
                number[pos++] = infix[i];
                i++;
            }
            i--;
            addToArray(output, number);
            printf("  Число %s -> выходной массив\n", number);
        }
        else if (c == '(') {
            pushStack(&operators, (double)c);
            printf("  ( -> стек операторов\n");
        }
        else if (c == ')') {
            while (!isEmptyStack(&operators) && (char)topStack(&operators) != '(') {
                char op[2] = { (char)popStack(&operators), 0 };
                addToArray(output, op);
                printf("  Оператор %s -> выходной массив\n", op);
            }
            if (!isEmptyStack(&operators)) popStack(&operators);
            printf("  ) -> удаляем из стека\n");
        }
        else if (isOperator(c)) {
            while (!isEmptyStack(&operators) && (char)topStack(&operators) != '(' &&
                getPriority((char)topStack(&operators)) >= getPriority(c)) {
                char op[2] = { (char)popStack(&operators), 0 };
                addToArray(output, op);
                printf("  Оператор %s -> выходной массив\n", op);
            }
            pushStack(&operators, (double)c);
            printf("  Оператор %c -> стек операторов\n", c);
        }
    }

    while (!isEmptyStack(&operators)) {
        char op[2] = { (char)popStack(&operators), 0 };
        addToArray(output, op);
        printf("  Оператор %s -> выходной массив\n", op);
    }

    freeStack(&operators);
}

// ========== ВЫЧИСЛЕНИЕ RPN ==========
double evaluateRPN(const char* rpn) {
    Stack st;
    initStack(&st);
    int len = strlen(rpn);

    printf("\n=== ВЫЧИСЛЕНИЕ RPN ===\n");

    for (int i = 0; i < len; i++) {
        if (rpn[i] == ' ') continue;

        if (isdigit(rpn[i])) {
            char numStr[64] = { 0 };
            int pos = 0;
            while (i < len && (isdigit(rpn[i]) || rpn[i] == '.')) {
                numStr[pos++] = rpn[i];
                i++;
            }
            i--;
            double num = atof(numStr);
            pushStack(&st, num);
            printf("  Помещаем %.2f в стек\n", num);
        }
        else if (isOperator(rpn[i])) {
            double b = popStack(&st);
            double a = popStack(&st);
            double result = applyOperator(a, b, rpn[i]);
            pushStack(&st, result);
            printf("  %.2f %c %.2f = %.2f -> в стек\n", a, rpn[i], b, result);
        }
    }

    double result = popStack(&st);
    freeStack(&st);
    return result;
}

// ========== ВЫЧИСЛЕНИЕ PN ==========
double evaluatePN(const char* pn) {
    Stack st;
    initStack(&st);
    int len = strlen(pn);

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
        else if (isOperator(pn[i])) {
            double a = popStack(&st);
            double b = popStack(&st);
            double result = applyOperator(a, b, pn[i]);
            pushStack(&st, result);
            printf("  %.2f %c %.2f = %.2f -> в стек\n", a, pn[i], b, result);
        }
    }

    double result = popStack(&st);
    freeStack(&st);
    return result;
}

// ========== ГЛАВНАЯ ФУНКЦИЯ ==========
int main() {
    setlocale(LC_ALL, "Russian");

    while (1) {
        system("cls");
        printf("Выберите режим:                         \n");
        printf("1. Инфиксная нотация                    \n");
        printf("2. Обратная польская нотация (RPN)      \n");
        printf("3. Прямая польская нотация (PN)         \n");
        printf("4. Выход                                \n");
        printf("Ваш выбор: ");

        int choice;
        scanf("%d", &choice);
        getchar();

        if (choice == 4) break;

        printf("Введите выражение: ");
        char input[256];
        fgets(input, 256, stdin);
        input[strcspn(input, "\n")] = 0;

        printf("Входные данные: %s\n", input);

        int valid = 0;
        double result = 0;

        switch (choice) {
        case 1: {
            valid = isValidExpression(input);
            if (!valid) {
                printf("Выходные данные: Invalid input\n");
            }
            else {
                Array rpn;
                initArray(&rpn);
                infixToRPN(input, &rpn);

                printf("\n  RPN: ");
                for (int i = 0; i < rpn.size; i++) {
                    printf("%s ", rpn.data[i]);
                }
                printf("\n");

                char rpnString[512] = { 0 };
                for (int i = 0; i < rpn.size; i++) {
                    strcat(rpnString, rpn.data[i]);
                    strcat(rpnString, " ");
                }
                result = evaluateRPN(rpnString);
                printf("\nВыходные данные: %.2f\n", result);
                freeArray(&rpn);
            }
            break;
        }
        case 2: {
            valid = isValidRPN(input);
            if (!valid) {
                printf("Выходные данные: Invalid input\n");
            }
            else {
                result = evaluateRPN(input);
                printf("\nВыходные данные: %.2f\n", result);
            }
            break;
        }
        case 3: {
            valid = isValidPN(input);
            if (!valid) {
                printf("Выходные данные: Invalid input\n");
            }
            else {
                result = evaluatePN(input);
                printf("\nВыходные данные: %.2f\n", result);
            }
            break;
        }

        }
        system("pause");
    }

    return 0;
}