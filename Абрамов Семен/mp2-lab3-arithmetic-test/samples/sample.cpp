#include<iostream>
#include<string>
#include<TFormula.h>
#include<Collection.h>

using namespace std;

int main()
{
	TForm form;
	string s;
	string sOut;

	cout << "Program for translation to Reverse Polish notation\n";
	cout << "(To finish enter \"exit\")\n";

	while (true)
	{
		try
		{
			cout << "Please enter a string: ";
			getline(cin, s);
			if (s == "exit") break;
			form.init(s);
			form.conversToRevPolEnt();
			sOut = form.get_oForm();
			cout << "Reverse Polish notation: " << sOut << endl;
			int ans = form.calcArithmExp();
			cout << "Answer: " << ans << endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
	return 0;
}