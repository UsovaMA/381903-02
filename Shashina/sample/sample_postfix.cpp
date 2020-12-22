#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
  string expression;
    double res;
    
  cout << "Введите арифметическое выражение: ";
  cin >> expression;
  cout << expression << endl;
    
  try 
  {
	  TPostfix postfix(expression);
	  cout << "Арифметическое выражение: " << postfix.getInfix() << endl;
	  postfix.ToPostfix();
	  cout << "Постфиксная форма: " << postfix.getPostfix() << endl;
      res = postfix.Calculate();
	  cout << "Результат выражения: " << res << endl;
  }
  catch (const char* s)
  {
	  cout << s;
  }
  return 0;
}
