#pragma once

template<typename T>
struct Stack {
    T* data;
    int size;
    int capacity;
};

template<typename T>
void initStack(Stack<T>* s) {
    s->capacity = 10;
    s->size = 0;
    s->data = new T[s->capacity];
}

template<typename T>
void pushStack(Stack<T>* s, T value) {
    if (s->size >= s->capacity) {
        int newCapacity = s->capacity * 2;
        T* newData = new T[newCapacity];

        for (int i = 0; i < s->size; i++) {
            newData[i] = s->data[i];
        }

        delete[] s->data;
        s->data = newData;
        s->capacity = newCapacity;
    }
    s->data[s->size++] = value;
}

template<typename T>
T popStack(Stack<T>* s) {
    if (s->size == 0) return T{};
    return s->data[--s->size];
}

template<typename T>
T topStack(Stack<T>* s) {
    if (s->size == 0) return T{};
    return s->data[s->size - 1];
}

template<typename T>
bool isEmptyStack(Stack<T>* s) {
    return s->size == 0;
}

template<typename T>
void freeStack(Stack<T>* s) {
    delete[] s->data;
    s->data = nullptr;
    s->size = 0;
    s->capacity = 0;
}