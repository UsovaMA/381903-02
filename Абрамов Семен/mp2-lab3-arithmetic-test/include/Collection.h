#pragma once

#include<iostream>
#include<exception>

using namespace std;

template <class T>
class ICollection {
public:
	virtual ~ICollection() {};
	virtual int getSize() const = 0;

	virtual void push(const T& v) = 0;
	virtual T& pop() = 0;
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
	Queue(const Queue<T>& q);
	Queue<T>& operator=(const Queue<T>& q);
	~Queue();

	bool operator==(const Queue<T>& q) const;

	int getSize() const;

	void push(const T& v);
	T& pop();
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
	Stack(const Stack<T>& s);
	Stack<T>& operator=(const Stack<T>& s);
	~Stack();

	bool operator==(const Stack<T>& q) const;

	int getSize() const;

	void push(const T& v);
	T& pop();
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
	pQueue = new T[n + 1];
	first = 0;
	last = n - 1;
}

template <class T>
Queue<T>::Queue(const Queue<T>& q)
{
	n = q.n;
	first = q.first;
	last = q.last;
	pQueue = new T[n];
	for (int i = 0; i < n; i++)
	{
		pQueue[i] = q.pQueue[i];
	}
}

template <class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& q)
{
	if (this == &q) return *this;
	delete[] pQueue;
	n = q.n;
	first = q.first;
	pQueue = new T[n];
	for (int i = 0; i < n; i++)
	{
		pQueue[i] = q.pQueue[i];
	}
	return *this;
}

template<class T>
Queue<T>::~Queue()
{
	delete[] pQueue;
}

template <class T>
bool Queue<T>::operator==(const Queue<T>& q) const
{
	if (n != q.n) return false;
	if (isEmpty() && q.isEmpty()) return true;
	if (!isEmpty() && q.isEmpty()) return false;
	if (isEmpty() && !q.isEmpty()) return false;

	int ind1 = first;
	int ind2 = q.first;
	while((ind1 != last) && (ind1 != q.last))
	{
		if (pQueue[ind1] != q.pQueue[ind1]) return false;
		ind1++;
		ind2++;
	}
	if ((ind1 != last) || (ind1 != q.last)) return false;

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
T& Queue<T>::pop()
{
	if (isEmpty()) { throw logic_error("queue_is_empty"); }
	int tmp = first;
	first = next(first);
	return pQueue[tmp];
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
Stack<T>::Stack(const Stack<T>& s)
{
	n = s.n;
	top = s.top;
	pStack = new T[n];
	for (int i = 0; i < n; i++)
	{
		pStack[i] = s.pStack[i];
	}
}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& s)
{
	if (this == &s) return *this;
	delete[] pStack;
	n = s.n;
	pStack = new T[n];
	top = s.top;
	for (int i = 0; i <= top; i++)
	{
		pStack[i] = s.pStack[i];
	}
	return *this;
}

template<class T>
inline Stack<T>::~Stack()
{
	delete[] pStack;
}

template <class T>
bool Stack<T>::operator==(const Stack<T>& s) const
{
	if (n != s.n) return false;
	if (top != s.top) return false;
	for (int i = 0; i < top; i++)
	{
		if (pStack[i] != s.pStack[i]) return false;
	}
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
	if (isFull()) { throw logic_error("stack_overflow"); }
	else {
		top++;
		pStack[top] = v;
	}
}

template <class T>
T& Stack<T>::pop()
{
	if (isEmpty()) { throw logic_error("stack_is_empty"); }
	int tmp = top;
	top--;
	return pStack[tmp];
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