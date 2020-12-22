#pragma once

#include <iostream>

const int MaxStackSize = 100;

template <class T>
class TStack
{
  T *pMem;
  int size;
  int top;
  TStack(const TStack &st) {}
  TStack& operator=(const TStack &st) {}
    
public:
    
  TStack(int _size)
  {
    size = _size;
    top = -1;
    if ((size < 1) || (size > MaxStackSize))
        throw std::logic_error("Invalid stack size");
    pMem = new T[size];
  }
    
  bool empty()
  {
	  return top == -1;
  }
    
  bool full()
  {
	  return top == (size - 1);
  }
    
  void push(T val)
  {
	  if (full())
		  throw std::logic_error("The stack is crowded");
	  pMem[++top] = val;
  }
    
  T pop()
  {
	  if (empty())
		  throw std::logic_error("The stack is empty");
	  return pMem[top--];
  }
    
  ~TStack()
  {
    delete [] pMem;
  }
    
};

