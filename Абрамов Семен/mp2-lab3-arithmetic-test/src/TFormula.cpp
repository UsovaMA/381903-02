#include<TFormula.h>

void TForm::LexAnal(ICollection<Lexem*>* q)
{
    string st;
    State state = q0;

    iForm += " ";
    int n = iForm.length();
    char c;

    for (int i = 0; i < n;i++)
    {
        c = iForm[i];
        if (state == q0)
        {
            st = c;
            if ((c >= '0') && (c <= '9'))
            {
                state = q2;
            }
            else if (c == '-')
            {
                q->push(new Lexem{st, UN});
            }
            else if (c == '(')
            {
                q->push(new Lexem{st, LP});
            }
            else if (c == ')')
            {
                state = q2;
                q->push(new Lexem{st, RP});
            }
            else if (c == ' ') {}
            else
            {
                throw logic_error("arithm_exp_invalid(LexAnal)");
            }
            continue;
        }
        if (state == q1)
        {
            st = c;
            if ((c >= '0') && (c <= '9'))
            {
                state = q2;
            }
            else if ((c == '+') || (c == '-') || (c == '*') || (c == '/'))
            {
                q->push(new Lexem{st, BIN});
            }
            else if (c == '(')
            {
                state = q0;
                q->push(new Lexem{st, LP});
            }
            else if (c == ')')
            {
                state = q1;
                q->push(new Lexem{st, RP});
            }
            else if (c == ' ') {}
            else
            {
                throw logic_error("arithm_exp_invalid(LexAnal)");
            }
            continue;
        }
        if (state == q2)
        {
            if ((c >= '0') && (c <= '9'))
            {
                st += c;
                state = q2;
            }
            else 
            {
                int v = atoi(st.c_str());
                q->push(new Lexem{st, VAL, v});
                state = q1;
                st = c;
                if ((c == '+') || (c == '-') || (c == '*') || (c == '/'))
                {
                    q->push(new Lexem{st, BIN});
                }
                else if (c == '(')
                {
                    q->push(new Lexem{st, LP});
                }
                else if (c == ')')
                {
                    state = q1;
                    q->push(new Lexem{st, RP});
                }
                else if (c == ' ') {}
                else
                {
                    throw logic_error("arithm_exp_invalid(LexAnal)");
                }
            }
        }
    }
}

void TForm::SyntAnal(ICollection<Lexem*>* qI, ICollection<Lexem*>* qO)
{
    State state;
    state = q0;
    int k = 0;
     
    while(!qI->isEmpty())
    {
        Lexem *l = qI->pop();
        if (qI->isEmpty()) state = q3;
        if (state == q0){
            if (l->te == LP) {
                k++;
                state = q0;
            }
            if ((l->te == VAL)) {
                state = q1;
            }
            if ((l->te == UN)) {
                state = q2;
            }
            if ((l->te == RP) || (l->te == BIN)) {
                throw logic_error("arithm_exp_invalid(SynAnal)");
            }
            qO->push(l);
            continue;
        }
        if (state == q1){
            if (l->te == RP) {
                k--;
                if (k < 0)  throw logic_error("arithm_exp_invalid(SynAnal)");
            }
            if ((l->te == BIN)) {
                state = q2;
            }
            if ((l->te == LP)|| (l->te == UN) || (l->te == VAL)) {
                throw logic_error("arithm_exp_invalid(SynAnal)");
            }
            qO->push(l);
            continue;
        }
        if (state == q2){
            if (l->te == LP) {
                k++;
                state = q0;
            }
            if ((l->te == VAL)) {
                state = q1;
            }
            if ((l->te == RP) || (l->te == BIN) || (l->te == UN)) {
                throw logic_error("arithm_exp_invalid(SynAnal)");
            }
            qO->push(l);
            continue;
        }
        if (state == q3){
            if (l->te == RP) {
                k--;
                if (k < 0)  throw logic_error("arithm_exp_invalid(SynAnal)");
            }
            if ((l->te == VAL)) {
            }
            if ((l->te == LP) || (l->te == BIN) || (l->te == UN)) {
                throw logic_error("arithm_exp_invalid(SynAnal)");
            }
            qO->push(l);
        }
    }
    if (k != 0)  throw logic_error("arithm_exp_invalid(SynAnal)");
}

TForm::TForm()
{
	ReadyOutForm = false;
    iForm = "";
    oForm = "";
    RevPolEnt = new Queue<Lexem*>(maxSizeCollection);
}

TForm::TForm(const string& str)
{
    if (str.length() == 0) throw logic_error("str_len_zero");
	iForm = str;
    oForm = "";
	ReadyOutForm = false;
    RevPolEnt = new Queue<Lexem*>(maxSizeCollection);
}

void TForm::init(const string& str)
{
    if (str.length() == 0) throw logic_error("str_len_zero");
	iForm = str;
    oForm = "";
	ReadyOutForm = false;
    while(!RevPolEnt->isEmpty())
    {
        RevPolEnt->pop();
    }
}

const string& TForm::get_iForm() const
{
	return iForm;
}

const string& TForm::get_oForm() const
{
    if (!ReadyOutForm) throw logic_error("output_form_is_not_ready");
	return oForm;
}

void TForm::conversToRevPolEnt()
{
    if (iForm.length() == 0) throw logic_error("str_is_not_initialized");
    ICollection<Lexem*>* q = new Queue<Lexem*>(maxSizeCollection);
    LexAnal(q);

    ICollection<Lexem*>* qN = new Queue<Lexem*>(maxSizeCollection);
    SyntAnal(q, qN);

    State state;
    state = q0;

    ICollection<Lexem*>* s = new Stack<Lexem*>(maxSizeCollection);
    while (!qN->isEmpty())
    {
        Lexem *l = qN->pop();
        if ((l->te == LP) || (l->te == UN)) {
            s->push(l);
        }
        if ((l->te == VAL)) {
            RevPolEnt->push(l);
            oForm += l->s;
            oForm += " "; 
        }
        if ((l->te == RP)) {
            while (!s->isEmpty()){
                l = s->pop();
                if (l->te != LP){
                    RevPolEnt->push(l);
                    oForm += l->s;
                }
                else
                {
                    break;
                }
            }
        }
        if ((l->te == BIN)) {
            Lexem* l1;
            if ((l->s == "+")||(l->s == "-"))
            {
                while(!s->isEmpty())
                {
                    l1 = s->pop();
                    if ((l1->te == BIN) || (l1->te == UN)){
                        RevPolEnt->push(l1);
                        oForm += l1->s;
                    }
                    else
                    {
                        s->push(l1);
                        break;
                    }
                }
            }
            else
            {
                while(!s->isEmpty())
                {
                    l1 = s->pop();
                    if (l1->te == BIN){
                        if ((l1->s == "*")||(l1->s == "/")){
                            RevPolEnt->push(l1);
                            oForm += l1->s;
                        }
                        else
                        {
                            s->push(l1);
                            break;
                        }
                        
                    }
                    else if (l1->te == UN) {
                        RevPolEnt->push(l1);
                        oForm += l1->s;
                    }
                    else
                    {
                        s->push(l1);
                        break;
                    }
                }
            }
            s->push(l);
        }
    }
    Lexem *l;
    while(!s->isEmpty())
    {
        l = s->pop();
        RevPolEnt->push(l);
        oForm += l->s;
    }
    ReadyOutForm = true;
	
	delete s;
    delete q;
    delete qN;
}

int TForm::calcArithmExp()
{
    if (!ReadyOutForm) throw logic_error("output_form_is_not_ready");
    ICollection<Lexem*>* str = new Stack<Lexem*>(maxSizeCollection);
    Lexem *l;
    while(!RevPolEnt->isEmpty())
    {
        l = RevPolEnt->pop();
        if (l->te == VAL)
        {
            str->push(l);
        }
        if (l->te == UN)
        {
            Lexem* l;
            int k;
            l = str->pop();
            k = -l->val;
            str->push(new Lexem{to_string(k),VAL, k});
        }
        if (l->te == BIN)
        {
            Lexem* l1;
            Lexem* l2;
            int k;
            if (l->s == "+")
            {
                l1 = str->pop();
                l2 = str->pop();
                k = l1->val + l2->val;
                str->push(new Lexem{to_string(k),VAL, k});
            }
            if (l->s == "-")
            {
                l1 = str->pop();
                l2 = str->pop();
                k = l2->val - l1->val;
                str->push(new Lexem{to_string(k),VAL, k});
            }
            if (l->s == "*")
            {
                l1 = str->pop();
                l2 = str->pop();
                k = l2->val * l1->val;
                str->push(new Lexem{to_string(k),VAL, k});
            }
            if (l->s == "/")
            {
                l1 = str->pop();
                l2 = str->pop();
                k = l2->val / l1->val;
                str->push(new Lexem{to_string(k),VAL, k});
            }
        }
    }
	int res = str->pop()->val;
	delete str;
	return res;
}