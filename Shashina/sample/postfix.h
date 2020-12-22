#pragma once

#include <string>
#include <iostream>
#include "stack.h"

using namespace std;

class TPostfix
{
  string infix;
  string postfix;
  string op = "+-*/^";
    
  int priority[5] = {1,1,2,2,3};
  bool Icorrect(string str);
public:
  TPostfix(string inf = "a+b")
  {
	 if (!Icorrect(inf))
		  throw std::logic_error("Incorrect expression");
	 for (int i = 0; i < inf.length(); i++)
	  if (inf[i] != ' ')
		 infix += inf[i];
	 if (infix.length() < 1)
		 throw std::logic_error("Error in infix length");
  }
  string getInfix() { return infix; }
  string getPostfix() { return postfix; }
  string ToPostfix();
  double Calculate(); 
};
