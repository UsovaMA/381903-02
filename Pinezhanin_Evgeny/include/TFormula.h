#pragma once

#include<iostream>
#include<string>
#include<map>
#include<limits>
#include<cmath>
#include<Collection.h>

using namespace std;

const int maxSizeCollection = 1000;

enum TypeElem {VALUE, VAR, UNARYOP, BINARYOP, LP, RP};
enum State {q0, q1, q2, q3};

struct Lexem {
	string s;
	TypeElem te;
    int val;
	int prior;

	Lexem(const string _s, const TypeElem _te, int _val = -1, int _prior = -1) : 
	s(_s), te(_te), val(_val), prior(_prior) { };
};

class TFormula {
	string inpFormula;
	string outFormula;
	bool isReadyOutFormula;

	Queue<Lexem*>* qRevPolNot;
	map<string, int>* vars;

    void LexicalAnalysis(ICollection<Lexem*>* q);
	void SyntacticAnalysis(ICollection<Lexem*>* qI, ICollection<Lexem*>* qO);
public:
	TFormula();
	TFormula(const string& str);

	void init(const string& str);

	const string& getInpFormula() const;
	const string& getOutFormula() const;
	bool isVars() const;
	bool setVars();

	void conversToRevPolNot();
	int calcArithmExp();
};