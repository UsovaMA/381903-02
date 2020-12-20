#pragma once
#include "list.h"

template <typename T>
class Stack
{
private:
    List<T> l1;
public:

    Stack();
    void put(T);
    T pop();
    bool isEmpty();
    void print();
};


template <typename T>
void Stack<T>::print()
{
    while(!isEmpty())
    {
        std::cout<<pop()<<" ";
    }
    std::cout<<std::endl;
}

template <typename T>
Stack<T>::Stack():l1(){}

template <typename T>
void Stack<T>::put(T val)
{
    l1.add_end(val);
}

template <typename T>
T Stack<T>::pop()
{
    if(isEmpty())
        return 0;

    T tmp=l1.get_last_val();
    l1.del_last();
    return tmp;
}

template <typename T>
bool Stack<T>::isEmpty()
{
    if(l1.get_max_index()<1)
        return true;
    return false;
}