#pragma once
const int MAX_STACK_SIZE = 1000;
const int MAX_QUEUE_SIZE = 1000;

template <class TC>
class VDynMem
{
public:
	virtual void push(const TC el) = 0;
	virtual TC pop() = 0;
	virtual bool isEmpty() const = 0;
	virtual bool isFull() const = 0;
};

template <class TC>
class Stack : public VDynMem<TC>
{
private:
	TC* mem;
	int Size;
	int hE;
public:
	Stack(int _size = MAX_STACK_SIZE) : Size(_size)
	{
		if ((_size <= 0) || (_size > MAX_STACK_SIZE)) throw std::logic_error("Invalid size stack.");
		mem = new TC[_size];
		hE = -1;
	}
	~Stack()
	{
		delete[]mem;
	}
	Stack(Stack& s) : Size(s.Size)
	{
		hE = 0;
		mem = new TC[Size];
		TC* temp = new TC[Size];
		int i = 0;
		while (!s.isEmpty())
		{
			temp[i] = s.pop();
			i++;
		}
		for (int j = 0; j < i; j++)
		{
			s.push(temp[j]);
			this->push(temp[j]);
		}
		delete[] temp;
	}
	bool Stack::operator==(Stack& s) const
	{
		if (Size != s.Size) return false;
		TC* temp = new TC[Size];
		int a;
		int i = 0;
		while (!s.isEmpty())
		{
			temp[i] = s.pop();
			a = this->pop();
			if (temp[i] != a)
			{
				for (int j = 0; j < i; j++)
				{
					s.push(temp[j]);
					this->push(temp[j]);
				}
				s.push(temp[i]);
				this->push(a);
				delete[] temp;
				return false;
			}
			i++;
		}
		for (int j = 0; j < i; j++)
		{
			s.push(temp[j]);
			this->push(temp[j]);
		}
		delete[] temp;
		return true;
	}
	bool Stack::operator!=(Stack& s) const
	{
		return !(this->operator==(s));
	}
	Stack& operator=(Stack& s)
	{
		if (this == &s)
			return *this;
		if (Size != s.Size)
		{
			delete[]mem;
			mem = new TC[s.Size];
			Size = s.Size;
		}
		hE = 0;
		TC* temp = new TC[Size];
		int i = 0;
		while (!s.isEmpty())
		{
			temp[i] = s.pop();
			i++;
		}
		for (int j = 0; j < i; j++)
		{
			s.push(temp[j]);
			this->push(temp[j]);
		}
		delete[] temp;
		return *this;
	}
	void push(const TC el)
	{
		if (isFull()) throw std::logic_error("Stack is full.");
		hE++;
		mem[hE] = el;
	}
	TC pop()
	{
		if (isEmpty()) throw std::logic_error("Stack is empty.");
		hE--;
		return mem[hE + 1];
	}
	bool isEmpty() const
	{
		return hE == -1;
	}
	bool isFull() const
	{
		return hE == Size - 1;
	}
};

template <class TC>
class Queue : public VDynMem<TC>
{
private:
	TC* mem;
	int Size;
	int lE;
	int hE;
	void incL() { lE = (lE + 1) % Size; }
	void incH() { hE = (hE + 1) % Size; }
public:
	Queue(int _size = MAX_QUEUE_SIZE) : Size(_size)
	{
		if ((_size <= 1) || (_size > MAX_QUEUE_SIZE)) throw std::logic_error("Invalid size queue.");
		mem = new TC[_size];
		hE = _size - 1;
		lE = 0;
	}
	~Queue()
	{
		delete[]mem;
	}
	Queue(Queue& q) : Size(q.Size)
	{
		lE = q.lE;
		hE = (lE - 1 + Size) % Size;
		mem = new TC[Size];
		TC* temp = new TC[Size];
		int i = 0;
		while (!q.isEmpty())
		{
			temp[i] = q.pop();
			i++;
		}
		for (int j = 0; j < i; j++)
		{
			q.push(temp[j]);
			this->push(temp[j]);
		}
		delete[] temp;
	}
	bool Queue::operator==(Queue& q) const
	{
		if (Size != q.Size) return false;
		TC* temp = new TC[Size];
		int a;
		int i = 0;
		while (!q.isEmpty())
		{
			temp[i] = q.pop();
			a = this->pop();
			if (temp[i] != a)
			{
				for (int j = 0; j < i; j++)
				{
					q.push(temp[j]);
					this->push(temp[j]);
				}
				q.push(temp[i]);
				this->push(a);
				delete[] temp;
				return false;
			}
			i++;
		}
		for (int j = 0; j < i; j++)
		{
			q.push(temp[j]);
			this->push(temp[j]);
		}
		delete[] temp;
		return true;
	}
	bool Queue::operator!=(Queue& q) const
	{
		return !(this->operator==(q));
	}
	Queue& operator=(Queue& q)
	{
		if (this == &q)
			return *this;
		if (Size != q.Size)
		{
			delete[]mem;
			mem = new TC[q.Size];
			Size = q.Size;
		}
		lE = q.lE;
		hE = (lE - 1 + Size) % Size;
		TC* temp = new TC[Size];
		int i = 0;
		while (!q.isEmpty())
		{
			temp[i] = q.pop();
			i++;
		}
		for (int j = 0; j < i; j++)
		{
			q.push(temp[j]);
			this->push(temp[j]);
		}
		delete[] temp;
		return *this;
	}
	void push(const TC el)
	{
		if (isFull()) throw std::logic_error("Queue is full.");
		incH();
		mem[hE] = el;
	}
	TC pop()
	{
		if (isEmpty()) throw std::logic_error("Queue is empty.");
		TC temp = mem[lE];
		incL();
		return temp;
	}
	bool isEmpty() const
	{
		return (hE + 1) % Size == lE;
	}
	bool isFull() const
	{
		return (hE + 2) % Size == lE;
	}
};