#pragma once

#include<iostream>
#include<string>
#include<Collection.h>

using namespace std;

const int maxSizeCollection = 1000;

enum TypeElem {VALUE, UNARYOP, BINARYOP, LP, RP};
enum State {q0, q1, q2, q3};

struct Lexem {
	string s;
	TypeElem te;
    int val;

	Lexem(const string _s, const TypeElem _te, int _val = -1) : s(_s), te(_te), val(_val) { };
};

class TFormula {
	string inpFormula;
	string outFormula;
	bool isReadyOutFormula;

	ICollection<Lexem*>* qRevPolNot;

    void LexicalAnalysis(ICollection<Lexem*>* q);
	void SyntacticAnalysis(ICollection<Lexem*>* qI, ICollection<Lexem*>* qO);
public:
	TFormula();
	TFormula(const string& str);

	void init(const string& str);

	const string& getInpFormula() const;
	const string& getOutFormula() const;

	void conversToRevPolNot();
	int calcArithmExp();
};