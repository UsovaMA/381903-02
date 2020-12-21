#include <iostream>
#include <string>
#include "arithmetic.h"

using namespace std;

//#define fast

#ifdef fast
int main()
{
	try
	{
		string s;
		getline(cin, s);

		Calculator calc(s);
		calc.printExpression();
		calc.nextStep();
		calc.printExpression();
		calc.nextStep();
		calc.printExpression();
}
	catch (const logic_error a)
	{
		cout << a.what() << endl;
	}
	return 0;
}
#endif // fast

#ifndef fast
int main()
{
	try
	{
		string s = "ad";
		Calculator calc;
		char c = 'e';
		bool next = true;
		while (next)
		{
			switch (c)
			{
			case 'e':
				cout << "Expression : ";
				do
					getline(cin, s);
				while (s.length() == 0);
				cout << "Answer : " << calc.getAnswer(s) << endl << "e - change expression, v - change values vars : ";
				cin >> c;
				break;
			case 'v':
				calc.changeValuesVar();
				cout << "Answer : " << calc.getAnswer(s) << endl << "e - change expression, v - change values vars : ";
				cin >> c;
				break;
			default:
				next = false;
				break;
			}
		}
	}
	catch (const logic_error a)
	{
		cout << a.what() << endl;
	}
	return 0;
}
#endif // !fast