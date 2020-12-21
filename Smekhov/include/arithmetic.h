#pragma once
#include "stack.h"
#include <map>
#include "objects.h"

enum State
{
	ready,
	number,
	var,
	afterBracket
};

class Parser
{
private:
	State state;
	int num;
	Object* obj;
public:
	Parser();
	bool creator(char symb);
	State getState();
	Object* getObject();
};

enum Step
{
	wait,
	calc,
	complete
};

class Calculator
{
private:
	string startExpression;
	Queue<Object*>* expressionAfterLex;
	Queue<Object*>* expressionAfterSynt;
	int answer;

	Object* copyObject(Object* obj) const;

	Step step;
	map<char, int> vars;
	void parseString(string s);
public:
	Calculator();
	~Calculator();
	void addExpression(string s);
	void calculate();
	int getAnswer();
	int getAnswer(string s);
	void changeValuesVar();
	string getStartExpression() const;
	Queue<Object*> getExpressionAfterLex() const;
	Queue<Object*> getExpressionAfterSynt() const;
};