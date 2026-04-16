#include "menu.hpp"

int current = 0;

string items[] =
{
    "Инфиксная нотация",
    "Обратная польская нотация (RPN)",
    "Прямая польская нотация (PN)",
    "Выход"
};

int countItems = 4;

void clear() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void clearInput() {
    cin.clear();
    cin.ignore(10000000, '\n');
}

void cin_ignore() {
    cin.ignore(100000, '\n');
}

void pause() {
    cout << '\n';
    system("Pause");
}

void hideCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void set_cords(int x, int y) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hStdout, pos);
}

void show_menu(int current, int size_items, const string items[], const string str) {
    hideCursor();
    set_cords(0, 0);
    cout << "=============== " << str << " ===============\n";
    for (int i = 0; i < size_items; i++) {
        if (i == current)
            cout << " -> " << items[i] << "\n";
        else
            cout << "    " << items[i] << "\n";
    }
}