#include "synt.h"
#include <iostream>

using namespace std;

int prioritet_op(char op);

Queue<string> Synt::synt_analiz(string str)
{
    Queue<string> polsk;
    Stack<char> oper;

    string tmp = "";
    char tmp_op = ' ';
    int op_priora_str = 0;
    int size=0;
    int size2=0;
    
    int g=0;
    int d=0;
    int v=0;

    int i = 0;
    while (i < str.length())
    {
        tmp = "";
        while ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'z'))
        {
            tmp += str[i];
            i++;
        }
        if(tmp!="")
        {
            //cout<<tmp<<": "<<g++<<endl;
            polsk.put(tmp);
            continue;
        }
        if(str[i]=='(')
        {
            size+=4;
            oper.put(str[i]);
            i++;
            continue;
        }

        if (oper.isEmpty())
        {
            oper.put(str[i]);
        }
        else
        {
            op_priora_str = prioritet_op(str[i])+size;

            while(!oper.isEmpty())
            {
                tmp_op = oper.pop();
                if(str[i]==')')
                {
                    size-=4;
                    while(tmp_op!='(')
                    {
                        tmp = tmp_op;
                        //cout<<tmp<<endl;
                        if(tmp!=")")
                            polsk.put(tmp);
                        tmp_op = oper.pop();
                    }
                    tmp_op=oper.pop();

                    if(tmp_op=='^')
                    {
                        tmp = tmp_op;
                        polsk.put(tmp);
                    }
                    else
                    {
                        oper.put(tmp_op);
                    }

                    break;
                }
                if (op_priora_str <= prioritet_op(tmp_op)+size)
                {
                    tmp = tmp_op;
                    //cout<<tmp<<"\t "<<tmp_op<<": "<<d++<<endl;
                    if(tmp!=")")
                        polsk.put(tmp);
                    
                }
                else
                {
                    //size2=size;
                    
                    oper.put(tmp_op);
                    
                    break;
                }
            }
            if(str[i]!=')');
                oper.put(str[i]);
           
            
        }
        i++;
    }

    while (!oper.isEmpty())
    {
        tmp_op = oper.pop();
        tmp = tmp_op;
        //cout<<tmp<<"\t "<<tmp_op<<": "<<v++<<endl;
        if(tmp!=")")    
            polsk.put(tmp);
    }

    return polsk;
}






int prioritet_op(char op)
{
    int t = 0;
    switch (op)
    {
    case '+':
        t = 1;
        break;
    case '-':
        t = 1;
        break;
    case '*':
        t = 2;
        break;
    case '/':
        t = 2;
        break;
    case '^':
        t=3;
        break;
    case ')':
        t = 0;
        break;
    case '(':
        t = 0;
        break;

    default:
        break;
    }
    return t;
}
