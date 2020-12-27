#pragma once
#include "stack.h"

#include <string>
#include <iostream>
using namespace std;

class Form
{
    string vir;
    string post;

    string operations = "+-*/^";
    int priority[5] = {1,1,2,2,3};

public:
Form(string s = "1+1");

bool isCorrect(string s);

string getVir() {return vir;}
string getPost() {return post;}

string post_vir();
double calc();

void sample();
};