#pragma once

#include <iostream>
using namespace std;

const int MaxStackSize = 100;

template <class T>
class TStack
{
    int size;
    int top;
    T *pMem;
    TStack(const TStack &st) {}
    TStack& operator=(const TStack &st) {}

public:

TStack(int _size)
{
    size = _size;
    top = -1;
    if ((size < 1) || (size > MaxStackSize)) throw logic_error("Invalid stack size");
    pMem = new T[size];
}

~TStack()
{
    delete[] pMem;
}

bool empty() {return top == -1;}

bool full() {return top == (size - 1);}

void push(T val)
{
    if (full()) throw logic_error("The stack is full");
    pMem[++top] = val;
}

T pop()
{
    if (empty()) throw logic_error("The stack is empty");
    return pMem[top--];
}
};