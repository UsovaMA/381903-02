#pragma once

#include<iostream>
#include<exception>

using namespace std;

template <class T>
class ICollection {
public:
	virtual int getSize() const = 0;

	virtual void push(const T& v) = 0;
	virtual T pop() = 0;
	virtual bool isEmpty() const = 0;
	virtual bool isFull() const = 0;
};

template <class T>
class Queue: public ICollection<T> {
	T* pQueue;
	int n;
	int last, first;

	int next(int i) const;
public:
	Queue(int _n = 100);
	Queue(Queue<T>& q);
	Queue<T>& operator=(Queue<T>& q);

	bool operator==(Queue<T>& q);

	int getSize() const;

	void push(const T& v);
	T pop();
	bool isFull() const;
	bool isEmpty() const;
};


template <class T>
class Stack: public ICollection<T> {
	T* pStack;
	int n;
	int top;
public:
	Stack(int _n = 100);
	Stack(Stack<T>& s);
	Stack<T>& operator=(Stack<T>& s);

	bool operator==(Stack<T>& q);

	int getSize() const;

	void push(const T& v);
	T pop();
	bool isFull() const;
	bool isEmpty() const;
};


template <class T>
int Queue<T>::next(int i) const
{
	return (i + 1) % n;
}

template <class T>
Queue<T>::Queue(int _n) :n(_n + 1)
{
	pQueue = new T[n];
	first = 0;
	last = n - 1;
}

template <class T>
Queue<T>::Queue(Queue<T>& q)
{
	n = q.n;
	first = 0;
	last = n - 1;
	pQueue = new T[n];
	T* tmpArray = new T[n];
	int count = 0;
	while(!q.isEmpty())
	{
		tmpArray[count] = q.pop();
		count++;
	}
	for (int i = 0; i < count; i++)
	{
		push(tmpArray[i]);
		q.push(tmpArray[i]);
	}
	delete[] tmpArray;
}

template <class T>
Queue<T>& Queue<T>::operator=(Queue<T>& q)
{
	if (this == &q) return *this;
	delete[] pQueue;
	n = q.n;
	first = 0;
	last = n - 1;
	pQueue = new T[n];
	T* tmpArray = new T[n];
	int count = 0;
	while(!q.isEmpty())
	{
		tmpArray[count] = q.pop();
		count++;
	}
	for (int i = 0; i < count; i++)
	{
		push(tmpArray[i]);
		q.push(tmpArray[i]);
	}
	return *this;
}

template <class T>
bool Queue<T>::operator==(Queue<T>& q)
{
	if (n != q.n) return false;

	Queue<T> tmp1(*this);
	Queue<T> tmp2(q);
	T tmpVal1;
	T tmpVal2;
	while((!tmp1.isEmpty()) && (!tmp2.isEmpty()))
	{
		tmpVal1 = tmp1.pop();
		tmpVal2 = tmp2.pop();
		if (tmpVal1 != tmpVal2) return false;
	}
	if ((!tmp1.isEmpty()) || (!tmp2.isEmpty())) return false;

	return true;
}

template <class T>
int Queue<T>::getSize() const
{
	return n - 1;
}

template <class T>
void Queue<T>::push(const T& v)
{
	if (isFull()){ throw logic_error("queue_overflow"); }
	last = next(last);
	pQueue[last] = v;
}

template <class T>
T Queue<T>::pop()
{
	if (isEmpty()) { throw logic_error("queue_is_empty"); }
	T tmp = pQueue[first];
	first = next(first);
	return tmp;
}

template <class T>
bool Queue<T>::isFull() const
{
	return next(next(last)) == first;
}

template <class T>
bool Queue<T>::isEmpty() const
{
	return next(last) == first;
}

template <class T>
Stack<T>::Stack(int _n): n(_n)
{
	if (_n < 0) throw logic_error("negative_number_of_elements");
	top = -1;
	pStack = new T[n];
}

template <class T>
Stack<T>::Stack(Stack<T>& s)
{
	n = s.n;
	top = -1;
	pStack = new T[n];
	T* tmpArray = new T[n];
	int count = 0;
	while(!s.isEmpty())
	{
		tmpArray[count] = s.pop();
		count++;
	}
	for (int i = count - 1; i >= 0; i--)
	{
		push(tmpArray[i]);
		s.push(tmpArray[i]);
	}
	delete[] tmpArray;
}

template <class T>
Stack<T>& Stack<T>::operator=(Stack<T>& s)
{
	if (this == &s) return *this;
	delete[] pStack;
	n = s.n;
	top = -1;
	pStack = new T[n];
	T* tmpArray = new T[n];
	int count = 0;
	while(!s.isEmpty())
	{
		tmpArray[count] = s.pop();
		count++;
	}
	for (int i = count - 1; i >= 0; i--)
	{
		push(tmpArray[i]);
		s.push(tmpArray[i]);
	}
	delete[] tmpArray;
	return *this;
}

template <class T>
bool Stack<T>::operator==(Stack<T>& s)
{
	if (n != s.n) return false;
	Stack<T> tmp1(*this);
	Stack<T> tmp2(s);
	T tmpVal1;
	T tmpVal2;
	while((!tmp1.isEmpty()) && (!tmp2.isEmpty()))
	{
		tmpVal1 = tmp1.pop();
		tmpVal2 = tmp2.pop();
		if (tmpVal1 != tmpVal2) return false;
	}

	if ((!tmp1.isEmpty()) || (!tmp2.isEmpty())) return false;
	return true;
}

template <class T>
int Stack<T>::getSize() const
{
	return n;
}

template <class T>
void Stack<T>::push(const T& v)
{
	if (isFull()) throw logic_error("stack_overflow");
	top++;
	pStack[top] = v;
}

template <class T>
T Stack<T>::pop()
{
	if (isEmpty()) { throw logic_error("stack_is_empty"); }
	T tmp = pStack[top];
	top--;
	return tmp;
}

template <class T>
bool Stack<T>::isFull() const
{
	return (n - 1 == top);
}

template <class T>
bool Stack<T>::isEmpty() const
{
	return (top == -1);
}