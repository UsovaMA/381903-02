#include "broadcast.h"
#include <vector>
#include <math.h>
#include <iostream>

using namespace std;


int perevod_str_in_int(string);
float perevod_str_in_float(string);
string perevod_float_in_str(float);
string perevod_int_in_str(int );

float Broadcast::broadcast(Queue<string>& q1,string dlya_perem)
{
    Stack<float> s1;
    vector<char> perem;
    vector<float> znach;
    string tmp = {""};
    bool exit = false;
    int z=0;

    for(int i=0;i<dlya_perem.length();i++)
    {
        if((dlya_perem[i]<'a'||dlya_perem[i]>'z'))
        {
            exit = false;   
            continue;
        }
        if(exit)
            {
                return 0.0f;
            }
        exit = true;
        for(int j=0;j<perem.size();j++)
        {
            if(perem[j]==dlya_perem[i])
            {
                continue;
            }
            z++;
            //cout<<dlya_perem[i]<<z<<endl;
            perem.push_back(dlya_perem[i]);
            break;
        }
        if(perem.empty())
        {
            
            perem.push_back(dlya_perem[i]);
        }
    }
    //cout<<perem.size()<<endl;

    for(int i=0;i<perem.size();i++)
    {
        int tmp=0;
        cout<<"Enter "<<perem[i]<<": ";
        cin >> tmp;
        znach.push_back(tmp);
    }

    //cout<<znach.size();

    while (!q1.isEmpty())
    {
        tmp = q1.pop();
        //cout<<tmp<<endl;
        float result=0.0f;
        if (tmp[0] != '+' && tmp[0] != '-' && tmp[0] != '*' && tmp[0] != '/'&&tmp[0] != '^')
        {
            float z=0.0f;

            if(tmp[0]>='0'&&tmp[0]<='9')
                z=perevod_str_in_float(tmp);
            else
            {
                for(int i=0;i<perem.size();i++)
                {
                    if(perem[i]==tmp[0])
                    {
                        z=znach[i];
                        break;
                    }
                }
            }
            
            
            //cout<<"Z: "<<z<<endl;
            s1.put(z);
            continue;
        }
        else
        {
            float b = s1.pop();
            float a = s1.pop();
            switch (tmp[0])
            {
            case '+':
                result = a + b;
                s1.put(result);
                break;
            case '-':
                result = a - b;
                s1.put(result);
                break;
            case '*':
                result = a * b;
                s1.put(result);
                break;
            case '/':
                result = a / b;
                s1.put(result);
                break;
            case '^':
                result = exp(log(a)*b);
                s1.put(result);
                break;

            default:
                break;
            }
            //cout<<a<<tmp[0]<<b<<endl;
            //cout<<tmp[0]<<endl;
            //cout<<"result: "<<result<<endl;
        }
    }

    //float d=s1.pop();    
    //string tmp2=perevod_float_in_str(d);

    return s1.pop();
}


int perevod_str_in_int(string str)
{
    int tmp=0;
    Stack<int> s;
    int z =str.length();
    for(int i=0;i<str.length();i++)
    {
        s.put(static_cast<int>(str[i])-48);
    }
    int i=0;
    while(!s.isEmpty())
    {
        
        tmp+=s.pop()*pow(10,i);
        i++;
    }
   
    return tmp;
}

float perevod_str_in_float(string str)
{
    int tmp=0;
    Stack<int> s;
    int z =str.length();
    for(int i=0;i<str.length();i++)
    {
        s.put(static_cast<float>(str[i])-48.0f);
    }
    int i=0;
    while(!s.isEmpty())
    {
        
        tmp+=s.pop()*pow(10,i);
        i++;
    }
   
    return tmp;
}

string perevod_int_in_str(int integ)
{
    if(integ==0)
    {
        string str={"0"};
        return str;
    }
    Stack<int> s;
    string str={""};
    int tmp=0;
    int i=1;
    while (integ)
    {
        int z = pow(10, i);
        tmp = integ % z / pow(10, i-1);
        s.put(tmp);
        integ-=tmp*pow(10,i-1);
        i++;
    }
    while(!s.isEmpty())
    {
        str+=static_cast<char>(s.pop()+48);
        
    }
    return str;
}

string perevod_float_in_str(float fl)
{
    string str={""};
    int tmpZ = static_cast<int>(fl);
    int tmpR = static_cast<int>((fl-tmpZ)*1000);

    str=perevod_int_in_str(tmpZ);
    str+=',';
    str+=perevod_int_in_str(tmpR);

    //cout<<str;

    return str;
}