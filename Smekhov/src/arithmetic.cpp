#include "arithmetic.h"

Parser::Parser()
{
	state = afterBracket;
	num = 0;
}

bool Parser::creator(char symb)
{
	if ((symb >= '0') && (symb <= '9'))
	{
		state = number;
		num = num * 10 + (symb - '0');
		return true;
	}
	if ((symb >= 'a') && (symb <= 'z'))
	{
		if (state == var)
		{
			state = ready;
			obj = new Operation('`');
			return false;
		}
		if (state == number)
		{
			state = var;
			obj = new Number(num);
			num = 0;
			return false;
		}
		state = var;
		obj = new Var(symb);
		return true;
	}
	if (state == afterBracket)
	{
		switch (symb)
		{
		case '(':
			state = afterBracket;
			obj = new Bracket(true);
			break;
		case ')':
			state = ready;
			obj = new Bracket(false);
			break;
		default:
			state = ready;
			obj = new Number(num);
			return false;
			break;
		}
		return true;
	}
	if (state == number)
	{
		state = ready;
		obj = new Number(num);
		num = 0;
		return false;
	}
	else
	{
		switch (symb)
		{
		case '(':
			if (state == var)
			{
				state = ready;
				obj = new Operation('`');
				return false;
			}
			else
			{
				state = afterBracket;
				obj = new Bracket(true);
			}
			break;
		case ')':
			state = ready;
			obj = new Bracket(false);
			break;
		default:
			state = ready;
			obj = new Operation(symb);
			break;
		}
		return true;
	}
}

State Parser::getState()
{
	return state;
}

Object* Parser::getObject()
{
	return obj;
}


Object* Calculator::copyObject(Object* obj) const
{
	Object* temp;
	switch (obj->getType())
	{
	case tNumber:
		temp = new Number(obj->getSomething());
		break;
	case tVar:
		temp = new Var(obj->getSomething());
		break;
	case tOperation:
		temp = new Operation(obj->getSomething(0));
		break;
	case tBrackets:
		temp = new Bracket(obj->getSomething());
		break;
	default:
		break;
	}
	return temp;
}

Calculator::Calculator()
{
	step = wait;
	expressionAfterLex = new Queue<Object*>;
	expressionAfterSynt = new Queue<Object*>;
}

Calculator::~Calculator()
{
	delete expressionAfterLex;
	delete expressionAfterSynt;
}

void Calculator::parseString(string s)
{
	startExpression = s;
	Parser p;
	for (int i = 0; i < s.size(); i++)
	{
		if (!(s[i] == ' '))
		{
			if (!p.creator(s[i]))
				i--;
			if (p.getState() != number)
			{
				Object* a = p.getObject();
				(*expressionAfterLex).push(a);
			}
		}
	}
	if (p.getState() == number)
	{
		p.creator('.');
		Object* a = p.getObject();
		(*expressionAfterLex).push(a);
	}
}

void Calculator::addExpression(string s)
{
	Object* a;
	while (!(*expressionAfterLex).isEmpty())
	{
		a = (*expressionAfterLex).pop();
		delete a;
	}
	while (!(*expressionAfterSynt).isEmpty())
	{
		a = (*expressionAfterSynt).pop();
		delete a;
	}
	parseString(s);
	step = calc;
	calculate();
}

bool correct(Queue<Object*> q1)
{
	bool b = true;
	Stack<Object*> par;
	Object* a = q1.pop();
	Types t = a->getType();
	if (t == tBrackets)
	{
		b = a->getSomething();
		if (b == 0)
			throw logic_error("Invalid position of the bracket!");
		par.push(a);
	}
	while (!q1.isEmpty())
	{
		a = q1.pop();
		switch (a->getType())
		{
		case tNumber:
			if (t == tBrackets)
			{
				if (b == false)
					throw logic_error("Number after closed bracket!");
			}
			t = tNumber;
			break;
		case tVar:
			t = tVar;
			break;
		case tOperation:
			if (t == tOperation)
				throw logic_error("Multiple operations in a row!");
			if ((char)a->getSomething(1) != '-')
				if (t == tBrackets)
					if (b == true)
						throw logic_error("Operation after opened bracket!");
			t = tOperation;
			break;
		case tBrackets:
			b = a->getSomething();
			if (b == 0)
			{
				if (par.isEmpty())
					throw logic_error("Invalid number of bracket!");
				par.pop();
			}
			else
			{
				if (t == tNumber)
					throw logic_error("Bracket after number!");
				par.push(a);
			}
			t = tBrackets;
			break;
		}

	}
	if (!par.isEmpty())
		throw logic_error("Invalid number of bracket!");
	return true;
}

void Calculator::calculate()
{
	switch (step)
	{
	case wait:
		return;
		break;
	case calc:
	{
		correct(*expressionAfterLex);
		Queue<Object*> copyLex(*expressionAfterLex);
		Stack<Object*> stack;
		Object* a;
		Object* b;
		while (!copyLex.isEmpty())
		{
			a = copyLex.pop();
			switch (a->getType())
			{
			case tNumber:
				(*expressionAfterSynt).push(copyObject(a));
				break;
			case tVar:
				(*expressionAfterSynt).push(copyObject(a));
				break;
			case tOperation:
				if (stack.isEmpty())
				{
					stack.push(a);
				}
				else
				{
					b = stack.pop();
					int pr1 = a->getSomething(), pr2 = b->getSomething();
					if (stack.isEmpty())
					{
						if (pr2 >= pr1)
						{
							if (b->getType() == tOperation)
								(*expressionAfterSynt).push(copyObject(b));
						}
						else
						{
							stack.push(b);
						}
					}
					else
					{
						while ((pr2 >= pr1) && (!stack.isEmpty()))
						{
							if (b->getType() == tOperation)
								(*expressionAfterSynt).push(copyObject(b));
							b = stack.pop();
							pr2 = b->getSomething();
						}
						if (pr2 < pr1)
							stack.push(b);
						else
							(*expressionAfterSynt).push(copyObject(b));
					}
					stack.push(a);
				}
				break;
			case tBrackets:
				if (a->getSomething() == 1)
					stack.push(a);
				else
				{
					b = stack.pop();
					while ((b->getType() == tOperation) && (!stack.isEmpty()))
					{
						(*expressionAfterSynt).push(copyObject(b));
						b = stack.pop();
					}
					if (b->getType() == tOperation)
						(*expressionAfterSynt).push(copyObject(b));
				}
				break;
			}
		}
		while (!stack.isEmpty())
		{
			a = stack.pop();
			(*expressionAfterSynt).push(copyObject(a));
		}

		Queue<Object*> copySynt(*expressionAfterSynt);
		int n1, n2;
		while (!copySynt.isEmpty())
		{
			a = copySynt.pop();
			switch (a->getType())
			{
			case tNumber:
				stack.push(a);
				break;
			case tVar:
				stack.push(a);
				break;
			case tOperation:
				b = stack.pop();
				if (b->getType() == tVar)
				{
					if (vars.find(b->getSomething()) != vars.end())
						n1 = vars[b->getSomething()];
					else
					{
						cout << b->getString() << " = ";
						cin >> n1;
						vars[b->getSomething()] = n1;
					}
				}
				else
					n1 = b->getSomething();
				b = stack.pop();
				if (b->getType() == tVar)
				{
					if (vars.find(b->getSomething()) != vars.end())
						n2 = vars[b->getSomething()];
					else
					{
						cout << b->getString() << " = ";
						cin >> n2;
						vars[b->getSomething()] = n2;
					}
				}
				else
					n2 = b->getSomething();
				b = new Number(a->getSomething(n2, n1));
				stack.push(b);
				break;
			}
		}
		step = complete;
		b = stack.pop();
		answer = b->getSomething();
		break;
	}
	case complete:
		return;
		break;
	default:
		break;
	}
}

int Calculator::getAnswer()
{
	if (step == wait) throw logic_error("Empty expression!");
	calculate();
	return answer;
}

int Calculator::getAnswer(string s)
{
	Object* a;
	while (!(*expressionAfterLex).isEmpty())
	{
		a = (*expressionAfterLex).pop();
		delete a;
	}
	while (!(*expressionAfterSynt).isEmpty())
	{
		a = (*expressionAfterSynt).pop();
		delete a;
	}
	parseString(s);
	step = calc;
	calculate();
	return answer;
}

void Calculator::changeValuesVar()
{
	for (auto& var : vars)
	{
		cout << var.first << " = ";
		cin >> var.second;
	}
}

string Calculator::getStartExpression() const
{
	if (step == wait) throw logic_error("Empty expression!");
	return startExpression;
}

Queue<Object*> Calculator::getExpressionAfterLex() const
{
	if (step == wait) throw logic_error("Empty expression!");
	Queue<Object*> copy(*expressionAfterLex);
	Queue<Object*> temp;
	while (!(copy.isEmpty()))
	{
		temp.push(copyObject(copy.pop()));
	}
	return temp;
}

Queue<Object*> Calculator::getExpressionAfterSynt() const
{
	if (step == wait) throw logic_error("Empty expression!");
	Queue<Object*> copy(*expressionAfterSynt);
	Queue<Object*> temp;
	while (!(copy.isEmpty()))
		temp.push(copyObject(copy.pop()));
	return temp;
}