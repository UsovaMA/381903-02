#include "leks.h"
#include <iostream>
#include "my_stack.h"

using namespace std;

bool Leks::leks_analiz(string str)
{
    Stack<char> scobochka;
    bool exit=false;
    int krugl=0;
    int figur=0;
    int kvadr=0;
    
    if(str[0]=='+'||str[0]=='-'||str[0]=='*'||str[0]=='/'||str[0]=='^')
        return false;

    for(int i=0;i<str.length();i++)
    {
        if(str[i]=='('||str[i]=='['||str[i]=='{')
        {
            switch (str[i])
                {
                case '(':
                    krugl++;
                    break;
                case '[':
                    kvadr++;
                    break;
                case '{':
                    figur++;
                    break;
                
                default:
                    return false;
                    break;
                }
            scobochka.put(str[i]);
            continue;
        }
        if(str[i]==')'||str[i]==']'||str[i]=='}')
        {
            char tmp=scobochka.pop();
            if(tmp)
            {
                switch (tmp)
                {
                case '(':
                    tmp=')';
                    krugl--;
                    break;
                case '[':
                    tmp=']';
                    kvadr--;
                    break;
                case '{':
                    tmp='}';
                    figur--;
                    break;
                
                default:

                    break;
                }

                if(tmp==str[i])
                {
                    continue;
                }
                else
                {
                    return false;
                }

            }
            else
            {
                return false;
            }
            
            
        }

        if(str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/'||str[i]=='^')
        {
            if(exit)
            {
                return false;
            }
            exit=true;
        }
        else
        {
            exit=false;
        }
    }
    if(figur*figur+kvadr*kvadr+krugl*krugl==0)
    {     
        return true;
    }
    return false;
}