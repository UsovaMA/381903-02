#include "stack.h"
#include "form.h"

#include <cmath>


Form::Form(string s)
{
    if (!isCorrect(s)) throw logic_error("isnt correct");

    for (int i = 0; i < s.length(); i++)
        if (s[i] != ' ') vir += s[i];

    if (vir.length() < 1) throw logic_error("vir len < 1");
}

bool Form:: isCorrect(string str)
{
    string zapresh = "!@#$%&?.,<>{}[]";
    int length = str.length(),
        l = 0,
        c = 0,
        op_num = 0;

    if ((operations.find(str[0]) != -1) || (operations.find(str[length - 1]) != -1)) return false;

    for (int i = 0; i < length; i++)
    {
        if (zapresh.find(str[i]) != -1) return false;

        if (str[i] == '(') c++;

        if (str[i] == ')') c--;

        if ((str[i] - 'a' >= 0) && (str[i] - 'a' <= 26)) l++;
        else l = 0;

        if (operations.find(str[i]) != -1) op_num++;
        else op_num = 0;

        if ((l > 1) || (op_num > 1)) return false;
    }

    if (c != 0) return false;

    return true;
}

string Form::post_vir()
{
    TStack<char> stack(MaxStackSize);
    string tmp = "+-*^/()";
    int len = vir.length();

    for (int i = 0; i < len; i++)
    {
        if (tmp.find(vir[i]) == -1) post += vir[i];

        if ((vir[i] >= '0') && (vir[i] <= '9'))
        {
            if (i != len)
            {
                if ((vir[i + 1] < '0') || (vir[i + 1] > '9')) post += ' ';
            }
            else post += ' ';
        }

        if (vir[i] == '(') stack.push(vir[i]);

        if (vir[i] == ')')
        {
            char t = stack.pop();

            while (t!= '(')
            {
                post += t;
                t = stack.pop();
            }
        }

        if (operations.find(vir[i]) != -1)
        {
            if (stack.empty()) stack.push(vir[i]);
            else
            {
                int i1 = operations.find(vir[i]);

                while (!stack.empty())
                {
                    char t = stack.pop();

                    if (t == '(')
                    {
                        stack.push(t);
                        break;
                    }

                    int i2 = operations.find(t);

                    if (priority[i1] <= priority[i2]) post += t;
                    else
                    {
                        stack.push(t);
                        break;
                    }
                }

                stack.push(vir[i]);
            }
        }
    }

    while (!stack.empty())
    {
        post += stack.pop();
    }

    return post;
}

double Form::calc()
{
    if (post.length() == 0) post_vir();

    int len = post.length();
    string var;
    TStack<double> stack(MaxStackSize);
    double *val = new double[len];

    for (int i = 0; i < len; i++)
    {
        if (operations.find(post[i]) == -1)
        {
            double p;

            if ((post[i] < 48) || (post[i] > 57))
            {
                if (var.find(post[i]) == -1)
                {
                    var += post[i];
                    cout << "Val of " << post[i] << ":" << endl;
                    cin >> p;
                    val[var.length() - 1] = p;
                }
                else p = val[var.find(post[i])];
            }
            else
            {
                string temp;

                while (post[i] != ' ')
                {
                    temp += post[i];
                    i++;
                }

                p = stoi(temp);
            }

            stack.push(p);
        }
        else
        {
            double t1, t2, t3;
            t1 = stack.pop();
            t2 = stack.pop();

            switch (post[i])
            {
            case '+': t3 = t1 + t2; break;
            case '-': t3 = t2 - t1; break;
            case '*': t3 = t1 * t2; break;
            case '/': t3 = t1 / t2; break;
            case '^': t3 = pow(t2, t1); break;
            }

            stack.push(t3);
        }
    }

    delete[] val;

    return stack.pop();
}

void Form::sample()
{
    double res;

    try
    {
        post_vir();
        cout << "Post. virazh.:" << endl;
        cout << getPost() << endl;

        res = calc();
        cout << "Res:" << endl << res << endl;
    }
    catch (const char* s)
    {
        cout << s << endl;
    }

    cout << endl << endl;
}