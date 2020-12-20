#pragma once
#include "list.h"

template <typename T>
class Queue
{
private:
    List<T> l1;
public:
    Queue():l1(){}
    //Queue(Queue&);
    void put(T);
    T pop();
    bool isEmpty();
    void print();
};

/*template <typename T>
Queue<T>::Queue(Queue& l2):l1()
{
    for(int i=1;i<=l1.get_max_index;i++)
    {
        l1.add_end(l2[i]);
    }
}
*/

template <typename T>
void Queue<T>::print()
{
    while(!isEmpty())
    {
        std::cout<<pop()<<" ";
    }
    std::cout<<std::endl;
}

template <typename T>
void Queue<T>::put(T val)
{
    l1.add_end(val);
}

template <typename T>
T Queue<T>::pop()
{
    if(isEmpty())
        {std::cout<<"\nQueue is empty!!\n";return 0;}
    T tmp=l1[1];
    l1.del_first();
    return tmp;
}

template <typename T>
bool Queue<T>::isEmpty()
{
    if(l1.get_max_index()<1)
        return true;
    return false;
}