#pragma once
#include <iostream>

template <typename T>
struct Link
{
    T val;
    Link* next;
};

template <typename T>
class List
{
private:
    Link<T>* first;
    int max_index;
public:
    List();
    void add_end(T);
    void add_begin(T);
    int get_max_index(){return max_index;}
    T operator[](int);
    T get_last_val();
    void print_all();
    bool del_el(int);
    bool del_last();
    bool del_first();
    ~List();
};


template <typename T>
List<T>::List()
{
    first = nullptr;
    max_index=0;
}

template <typename T>
void List<T>::add_end(T val)
{
    max_index++;
    Link<T>* tmp = new Link<T>;
    tmp->val=val;
    tmp->next=first;
    first=tmp;
}

template <typename T>
void List<T>::add_begin(T val)
{
    max_index++;
    Link<T>* tmp = new Link<T>;
    while(tmp->next)
    {
        tmp=tmp->next;
    }
    Link<T>* tmp1 = new Link<T>;
    tmp1->val=val;
    tmp1->next=nullptr;
    tmp->next=tmp1;

    return;
}

template <typename T>
T List<T>::operator[](int index)
{
    if(index>max_index||index<1)
        return 0;

    Link<T>* tmp = first;
    for(int i=0;i<max_index-index;i++)
    {
        tmp=tmp->next;
    }    
    
    return tmp->val;
}

template <typename T>
T List<T>::get_last_val()
{
    return first->val;
}

template <typename T>
void List<T>::print_all()
{
    Link<T>* tmp = first;
    while(tmp)
    {
        std::cout<<tmp->val<<"  ";
        tmp=tmp->next;
    }
    std::cout<<std::endl;
    return;
}



template <typename T>
bool List<T>::del_el(int a) 
{
    if(a>max_index||a<2)
        return false;
    
    if(max_index==1)
    {
     //   del_last();
        return true;
    }

    Link<T>* tmp=first;

    max_index--;
    for(int i=0;i<max_index-a;i++)
        tmp=tmp->next;
    
    Link<T>* tmp_next=tmp->next;
    tmp->next=tmp_next->next;
    delete tmp_next;
    

    return true;
}

template <typename T>
bool List<T>::del_last() 
{
    if(max_index<1)
        return false;

    Link<T>* tmp=first;
    first=first->next;
    delete tmp;
    max_index--;

    return true;
}

template <typename T>
bool List<T>::del_first() 
{
    if(max_index<1)
        return false;
    if(max_index==1)
    {
        del_last();
        return true;
    }

    Link<T>* tmp=first;
    while(tmp->next->next)
    {
        tmp=tmp->next;
    }
    delete tmp->next;
    tmp->next = nullptr;
    max_index--;

    return true;
}

template <typename T>
List<T>::~List()
{
    Link<T>* tmp=first;
    while(first)
    {
        tmp=first;
        first=first->next;
        delete tmp;
    }
    //std::cout<<"I delete!\n";
}