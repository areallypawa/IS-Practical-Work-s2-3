#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cctype>
#include <cmath>
#include <conio.h>
#include "menu.hpp"
#include "Reverse_polish_notation.hpp"
#include "Polish_notation.hpp"
using namespace std;


int main() {
    setlocale(LC_ALL, "Russian");
    string input;

    do {
        clear();
       
        while (true) {
            show_menu(current, countItems, items, "МЕНЮ");
            int key = _getch();

            if (key == 72 && current > 0) current--;
            if (key == 80 && current < countItems - 1) current++;
            if (key == 13) break;
        }
        
        if (current == 3) { 
            clearInput();
            break; 
        }

       /* cin.ignore(1000000, '\n');*/

        cout << "Введите выражение: ";
        getline(cin, input);
        clear();
        cout << "Входные данные: " << input << '\n';

        int valid = 0;
        double result = 0;

        switch (current) {
        case 0: {
            
            valid = isValidExpression(input);
            if (!valid) {
                cout << "Выходные данные : Invalid input\n";
            }
            else {
                string rpn = infixToRPN(input);
                pause();
                clear();
                cout << "Входные данные: " << rpn << endl;
                string pn = RPNtoPN(rpn);
                pause();
                clear();
                cout << "Входные данные: " << rpn << endl;
                result = evaluateRPN(rpn);
                cout << "\nВыходные данные: " << result << "\n";
            }
            break;
        }
        case 1: {
            valid = isValidRPN(input);
            if (!valid) {
                cout << "Выходные данные: Invalid input\n";
            }
            else {
                result = evaluateRPN(input);
                printf("\nВыходные данные: %.2f\n", result);
            }
            break;
        }
        case 2: {
            valid = isValidPN(input);
            if (!valid) {
                cout << "Выходные данные: Invalid input\n";
            }
            else {
                result = evaluatePN(input);
                printf("\nВыходные данные: %.2f\n", result);
            }
            break;
        }

        }
        pause();
    } while (true);

    return 0;
}