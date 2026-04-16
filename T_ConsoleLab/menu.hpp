#pragma once
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

extern int current;
extern string items[];
extern int countItems;

void clear();
void clearInput();
void cin_ignore();
void pause();

void hideCursor();
void set_cords(int x, int y);
void show_menu(int current, int size_items, const string items[], const string str);