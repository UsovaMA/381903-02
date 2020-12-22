#include<TFormula.h>

void TFormula::LexicalAnalysis(ICollection<Lexem*>* q)
{
    string st;
    State state = q0;
    inpFormula += " ";
    int n = inpFormula.length();
    char c;

    for (int i = 0; i < n; i++)
    {
        c = inpFormula[i];
        if (state == q0)
        {
            st = c;
            if ((c >= '0') && (c <= '9'))
            {
                state = q2;
            }
            else if ((c >= 'a') && (c <= 'z'))
            {
                state = q3;
                (*vars)[st] = 0;
                q->push(new Lexem(st, VAR));
            }
            else if (c == '-')
            {
                state = q1;
                q->push(new Lexem(st, UNARYOP));
            }
            else if (c == '(')
            {
                q->push(new Lexem(st, LP));
            }
            else if (c == ')')
            {
                state = q3;
                q->push(new Lexem(st, RP));
            }
            else if (c == ' ') {}
            else
            {
                if ((c == '+') || (c == '^') || (c == '*') || (c == '/'))
                {
                    throw logic_error("Arithmetic expression is invalid(The binary operation is in the wrong place)");
                }
                else 
                {
                    throw logic_error("Arithmetic expression is invalid(Incorrect characters in the expression)");
                }
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
            else if ((c == '+') || (c == '-'))
            {
                q->push(new Lexem(st, BINARYOP, -1, 1));
            }
            else if ((c == '*') || (c == '/'))
            {
                q->push(new Lexem(st, BINARYOP, -1, 2));
            }
            else if (c == '^')
            {
                q->push(new Lexem(st, BINARYOP, -1, 3));
            }
            else if ((c >= 'a') && (c <= 'z'))
            {
                state = q3;
                (*vars)[st] = 0;
                q->push(new Lexem(st, VAR));
            }
            else if (c == '(')
            {
                state = q0;
                q->push(new Lexem(st, LP));
            }
            else if (c == ')')
            {
                state = q3;
                q->push(new Lexem(st, RP));
            }
            else if (c == ' ') {}
            else
            {
                throw logic_error("Arithmetic expression is invalid(Incorrect characters in the expression)");
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
                q->push(new Lexem(st, VALUE, v));
                state = q1;
                st = c;
                if ((c == '+') || (c == '-'))
                {
                    q->push(new Lexem(st, BINARYOP, -1, 1));
                }
                else if ((c == '*') || (c == '/'))
                {
                    q->push(new Lexem(st, BINARYOP, -1, 2));
                }
                else if (c == '^')
                {
                    q->push(new Lexem(st, BINARYOP, -1, 3));
                }
                else if ((c >= 'a') && (c <= 'z'))
                {
                    state = q3;
                    (*vars)[st] = 0;
                    q->push(new Lexem("*", BINARYOP, -1, 2));
                    q->push(new Lexem(st, VAR));
                }
                else if (c == '(')
                {
                    state = q0;
                    q->push(new Lexem(st, LP));
                }
                else if (c == ')')
                {
                    state = q3;
                    q->push(new Lexem{st, RP});
                }
                else if (c == ' ') {}
                else
                {
                    throw logic_error("Arithmetic expression is invalid(Incorrect characters in the expression)");
                }
            }
            continue;
        }
        if (state == q3)
        {
            st = c;
            if ((c >= 'a') && (c <= 'z'))
            {
                state = q3;
                (*vars)[st] = 0;
                q->push(new Lexem("*", BINARYOP, -1, 2));
                q->push(new Lexem(st, VAR));
            }
            else if ((c >= '0') && (c <= '9'))
            {
                q->push(new Lexem("*", BINARYOP, -1, 2));
                state = q2;
            }
            else if ((c == '+') || (c == '-'))
            {
                state = q1;
                q->push(new Lexem(st, BINARYOP, -1, 1));
            }
            else if ((c == '*') || (c == '/'))
            {
                state = q1;
                q->push(new Lexem(st, BINARYOP, -1, 2));
            }
            else if (c == '^')
            {
                state = q1;
                q->push(new Lexem(st, BINARYOP, -1, 3));
            }
            else if (c == '(')
            {
                state = q0;
                q->push(new Lexem("*", BINARYOP, -1, 2));
                q->push(new Lexem(st, LP));
            }
            else if (c == ')')
            {
                q->push(new Lexem(st, RP));
            }
            else if (c == ' ') {}
            else
            {
                throw logic_error("Arithmetic expression is invalid(Incorrect characters in the expression)");
            }
        }
    }
}

void TFormula::SyntacticAnalysis(ICollection<Lexem*>* qI, ICollection<Lexem*>* qO)
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
            if ((l->te == VALUE) || (l->te == VAR) ) {
                state = q1;
            }
            if (l->te == UNARYOP) {
                state = q2;
            }
            if ((l->te == RP)) {
                throw logic_error("Arithmetic expression is invalid(Incorrect parentheses)");
            }
            if ((l->te == BINARYOP)) {
                throw logic_error("Arithmetic expression is invalid(The binary operation is in the wrong place)");
            }
            qO->push(l);
            continue;
        }
        if (state == q1){
            if (l->te == RP) {
                k--;
                if (k < 0)  throw logic_error("Arithmetic expression is invalid(Incorrect parentheses)");
            }
            if ((l->te == BINARYOP)) {
                state = q2;
            }
            if ((l->te == LP)) {
                throw logic_error("Arithmetic expression is invalid(Incorrect parentheses)");
            }
            if ((l->te == UNARYOP)) {
                throw logic_error("Arithmetic expression is invalid(The unary operation is in the wrong place)");
            }
            qO->push(l);
            continue;
        }
        if (state == q2){
            if (l->te == LP) {
                k++;
                state = q0;
            }
            if ((l->te == VALUE) || (l->te == VAR)) {
                state = q1;
            }
            if ((l->te == RP)) {
                throw logic_error("Arithmetic expression is invalid(Incorrect parentheses)");
            }
            if ((l->te == BINARYOP)) {
                throw logic_error("Arithmetic expression is invalid(The binary operation is in the wrong place)");
            }
            qO->push(l);
            continue;
        }
        if (state == q3){
            if (l->te == RP) {
                k--;
                if (k < 0)  throw logic_error("Arithmetic expression is invalid(Incorrect parentheses)");
            }
            if ((l->te == LP)) {
                throw logic_error("Arithmetic expression is invalid(Incorrect parentheses)");
            }
            if ((l->te == UNARYOP)) {
                throw logic_error("Arithmetic expression is invalid(The unary operation is in the wrong place)");
            }
            if ((l->te == BINARYOP)) {
                throw logic_error("Arithmetic expression is invalid(The binary operation is in the wrong place)");
            }
            qO->push(l);
        }
    }
    if (k != 0)  throw logic_error("Arithmetic expression is invalid(Incorrect parentheses)");
}

TFormula::TFormula()
{
	isReadyOutFormula = false;
    inpFormula = "";
    outFormula = "";
    qRevPolNot = new Queue<Lexem*>(maxSizeCollection);
    vars = new map<string, int>;
}

TFormula::TFormula(const string& str)
{
    if (str.length() == 0) throw logic_error("String length is zero");
	inpFormula = str;
    outFormula = "";
	isReadyOutFormula = false;
    qRevPolNot = new Queue<Lexem*>(maxSizeCollection);
    vars = new map<string, int>;
}

void TFormula::init(const string& str)
{
    if (str.length() == 0) throw logic_error("String length is zero");
	inpFormula = str;
    outFormula = "";
	isReadyOutFormula = false;
    vars->clear();
    while(!qRevPolNot->isEmpty())
    {
        qRevPolNot->pop();
    }
}

const string& TFormula::getInpFormula() const
{
	return inpFormula;
}

const string& TFormula::getOutFormula() const
{
    if (!isReadyOutFormula) throw logic_error("The output formula is not ready");
	return outFormula;
}

bool TFormula::isVars() const
{
    return !vars->empty();
}

bool TFormula::setVars()
{
    if (!isVars()) return isVars(); 
    for (auto& var : *vars)
	{
		cout << var.first << " = ";
		cin >> var.second;
        if (cin.fail()) 
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw logic_error("Invalid value");
        }
	}
    return true;
}

void TFormula::conversToRevPolNot()
{
    if (inpFormula.length() == 0) throw logic_error("String is not initialized");
    ICollection<Lexem*>* q = new Queue<Lexem*>(maxSizeCollection);
    LexicalAnalysis(q);

    //while(!q->isEmpty())
    //{
    //    Lexem* l = q->pop();
    //    cout << l->s << " " << l->te << " " << l->val << endl;
    //}

    ICollection<Lexem*>* qN = new Queue<Lexem*>(maxSizeCollection);
    SyntacticAnalysis(q, qN);

    //while(!qN->isEmpty())
    //{
    //    Lexem* l = qN->pop();
    //    cout << l->s << " " << l->te << " " << l->val << endl;
    //}

    State state;
    state = q0;

    ICollection<Lexem*>* s = new Stack<Lexem*>(maxSizeCollection);
    while (!qN->isEmpty())
    {
        Lexem *l = qN->pop();
        if ((l->te == LP) || (l->te == UNARYOP)) {
            s->push(l);
        }
        if ((l->te == VALUE) || (l->te == VAR)) {
            qRevPolNot->push(l);
            outFormula += l->s;
            outFormula += " "; 
        }
        if ((l->te == RP)) {
            while (!s->isEmpty()){
                l = s->pop();
                if (l->te != LP){
                    qRevPolNot->push(l);
                    outFormula += l->s;
                }
                else
                {
                    break;
                }
            }
        }
        if ((l->te == BINARYOP)) {
            Lexem* l1;
            while(!s->isEmpty())
            {
                l1 = s->pop();
                if (l1->te == UNARYOP){
                    qRevPolNot->push(l1);
                    outFormula += l1->s;
                }
                else if ((l1->te == BINARYOP) && (l1->prior >= l->prior)){
                    qRevPolNot->push(l1);
                    outFormula += l1->s;
                }
                else
                {
                    s->push(l1);
                    break;
                }
            }
            s->push(l);
        }
    }
    Lexem *l;
    while(!s->isEmpty())
    {
        l = s->pop();
        qRevPolNot->push(l);
        outFormula += l->s;
    }
    isReadyOutFormula = true;
}

int TFormula::calcArithmExp()
{
    if (!isReadyOutFormula) throw logic_error("The output formula is not ready");
    ICollection<Lexem*>* s = new Stack<Lexem*>(maxSizeCollection);
    Queue<Lexem*>* qRevPolNotTmp = new Queue<Lexem*>(maxSizeCollection);
    *qRevPolNotTmp = *qRevPolNot; 
    Lexem *l;
    while(!qRevPolNotTmp->isEmpty())
    {
        l = qRevPolNotTmp->pop();
        if (l->te == VALUE)
        {
            s->push(l);
        }
        if (l->te == VAR)
        {
            s->push(new Lexem(l->s,VALUE, (*vars)[l->s]));
        }
        if (l->te == UNARYOP)
        {
            Lexem* l;
            int k;
            l = s->pop();
            k = -l->val;
            s->push(new Lexem{to_string(k),VALUE, k});
        }
        if (l->te == BINARYOP)
        {
            Lexem* l1;
            Lexem* l2;
            int k;
            if (l->s == "+")
            {
                l1 = s->pop();
                l2 = s->pop();
                k = l1->val + l2->val;
                s->push(new Lexem{to_string(k),VALUE, k});
            }
            if (l->s == "-")
            {
                l1 = s->pop();
                l2 = s->pop();
                k = l2->val - l1->val;
                s->push(new Lexem{to_string(k),VALUE, k});
            }
            if (l->s == "*")
            {
                l1 = s->pop();
                l2 = s->pop();
                k = l2->val * l1->val;
                s->push(new Lexem{to_string(k),VALUE, k});
            }
            if (l->s == "/")
            {
                l1 = s->pop();
                l2 = s->pop();
                k = l2->val / l1->val;
                s->push(new Lexem{to_string(k),VALUE, k});
            }
            if (l->s == "^")
            {
                l1 = s->pop();
                l2 = s->pop();
                k = pow(l2->val,l1->val);
                s->push(new Lexem{to_string(k),VALUE, k});
            }
        }
    }
	return s->pop()->val;
}