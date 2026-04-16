#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>

using namespace std;

extern string items[];

#define GREEN	"\033[32m"
#define YELLOW	"\033[33m"
#define RED		"\033[31m"
#define RESET   "\033[0m"

extern int current;
extern int countItems;

struct Stack {
    char* data;
    int size;
    int capacity;
};

void clear();
void pause();
void clearInput();
void cin_ignore();
void show_menu(int current, int size_items, const string items[], string str);