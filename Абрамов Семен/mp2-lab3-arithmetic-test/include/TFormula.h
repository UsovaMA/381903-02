#pragma once

#include<iostream>
#include<string>
#include<Collection.h>

using namespace std;

const int maxSizeCollection = 500;

enum State { q0, q1, q2, q3 };
enum TypeElem {VAL, UN, BIN, LP, RP};


struct Lexem {
	TypeElem te;
	string s;
	
    int val;
public:
	Lexem(string _s, TypeElem _te, int _val = -1) : s(_s), te(_te), val(_val) {};
};

class TForm {
	string iForm;
	string oForm;
	bool ReadyOutForm;

	ICollection<Lexem*>* RevPolEnt;

    void LexAnal(ICollection<Lexem*>* q);
	void SyntAnal(ICollection<Lexem*>* qI, ICollection<Lexem*>* qO);
public:
	TForm();
	TForm(const string& str);

	void init(const string& str);

	const string& get_iForm() const;
	const string& get_oForm() const;

	void conversToRevPolEnt();
	int calcArithmExp();
};