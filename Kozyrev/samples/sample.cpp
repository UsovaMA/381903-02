#include "form.h"

#include <string>
#include <iostream>
using namespace std;

int main()
{

    while (true)
    {
        string s;
        cout << "Virazhenie:" << endl;
        cin >> s;

        Form f(s);
        f.sample();
    }

    return 0;
}