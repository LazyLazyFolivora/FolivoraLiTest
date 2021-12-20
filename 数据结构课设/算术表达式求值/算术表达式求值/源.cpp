// @author: Folivora Li
// @copyright: Folivora Li

/*
17����2���������ʽ��ֵ (ѡ��) ��ջ��
[��������]
����һ���������ʽ���ɲ�����(operand)�������(operator)�ͽ��޷�(delimiter)��ɵġ�
  �������������ʵ���������ֻ���Ӽ��˳�����������������޷����������źͱ��ʽ��ʼ����������#����
  �磺#6+15*��21-8/4��#��������ʽ��ʼ����������Ϊ�˷��㡣
  ������á���������ȷ������������ʽ��ֵ��
[����Ҫ��]
��1�� �Ӽ��̻��ļ�����һ���Ϸ����������ʽ�������ȷ�Ľ����
��2�� ��ʾ�������к�ջ�ı仯���̡�
��3�� �����㷨�Ľ�׳�ԣ������ʽ����ʱ��Ҫ��������ԭ�����ʾ��
��4�� ʵ�ַ������Ĵ�*/

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <sstream>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
using namespace std;
typedef struct {
    string sign = "";
    int priority;
}Operator;
typedef struct {
    Operator* base;
    Operator* top;
    int stacksize;
}SqStack;
void InitStack(SqStack& s)
{
    s.base = new Operator[STACK_INIT_SIZE];
    if (s.base == NULL)
    {
        cout << "error" << endl;
        exit(1);
    }
    s.stacksize = STACK_INIT_SIZE;
    s.top = s.base;
    s.top->sign = "";
    
}
void Push(SqStack& s, Operator data)
{
    if (s.top - s.base >= s.stacksize)
    {
        //s.base = (Operator*)realloc(s.base, (s.stacksize + STACKINCREMENT) * sizeof(Operator));
        if (s.base == NULL)
        {
            cout << "error" << endl;
            exit(1);
        }
        s.top = s.base + s.stacksize;
        s.stacksize += STACKINCREMENT;
    }
    s.top->priority = data.priority;
    s.top->sign = data.sign;
    s.top++;
    
}
void Pop(SqStack& s)
{
    s.top--;
}

Operator Gettop(SqStack s)
{
    return *(--s.top);
}

void PrintStack(SqStack s)
{
    while (s.top - s.base > 0)
    {
        s.top--;
        cout << s.top->sign << "  ";
    }
    cout << endl;
}
bool EmptyStack(SqStack s)
{
    if (s.top <= s.base)
    {
        return true;
    }
    return false;
}
bool Check(vector<string>& expression_vec)
{
    for (int i = 0; i < expression_vec.size() - 1; i++)
    {
        if (((expression_vec[i] == "+") || (expression_vec[i] == "-") || (expression_vec[i] == "*") || (expression_vec[i] == "/") || (expression_vec[i] == "(")) && ((expression_vec[i + 1] == "+") || (expression_vec[i + 1] == "-") || (expression_vec[i + 1] == "*") || (expression_vec[i + 1] == "/") || (expression_vec[i + 1] == ")")))
        {
            cout << "���ܽ�" << expression_vec[i] << "��" << expression_vec[i + 1] << "�������ŷ�һ��" << endl;
            return false;
        }
    }
    return true;
}
void TurnBack(vector<string>& expression_vec, vector<string>& back_expression_vec)
{
    SqStack s;
    InitStack(s);
    for (int i = 0; i < expression_vec.size(); i++)
    {
        if ((expression_vec[i] != "+") && (expression_vec[i] != "-") && (expression_vec[i] != "*") && (expression_vec[i] != "/") && (expression_vec[i] != "(") && (expression_vec[i] != ")"))
        {
            back_expression_vec.push_back(expression_vec[i]);
        }
        else
        {
            Operator temp;
            temp.sign = expression_vec[i];
            if ((expression_vec[i] == "+") || (expression_vec[i] == "-"))
            {
                temp.priority = 1;
            }
            else if ((expression_vec[i] == "*") || (expression_vec[i] == "/"))
            {
                temp.priority = 2;
            }
            else if(expression_vec[i]=="(")
            {
                temp.priority = 3;
            }
            else
            {
                temp.priority = -1;
            }
            if ((EmptyStack(s)) || (Gettop(s).priority < temp.priority))
            {
                if (temp.priority == 3)
                {
                    temp.priority = 0;
                }
                Push(s, temp);
            }
            else
            {
                if (temp.priority == -1)
                {
                    //Pop(s);
                    while ((Gettop(s).sign != "("))
                    {
                        back_expression_vec.push_back(Gettop(s).sign);
                        Pop(s);
                    }
                    Pop(s);
                }
                else
                {
                    while (temp.priority <= Gettop(s).priority)
                    {
                        back_expression_vec.push_back(Gettop(s).sign);
                        Pop(s);
                        if (EmptyStack(s))
                        {
                            break;
                        }
                    }
                    Push(s, temp);
                    
                }
                
            }
        }
        PrintStack(s);
    }
    while (!EmptyStack(s))
    {
        back_expression_vec.push_back(Gettop(s).sign);
        Pop(s);
    }
}
template <class Type>
Type stringToNum(const string& str)
{
    istringstream iss(str);
    Type num;
    iss >> num;
    return num;
}
string NumToString(float Num)
{
    ostringstream oss;
    oss << Num;
    string str(oss.str());
    return str;
}
int main()
{ 
  
    char a;
    cout << "����#��Ϊ��ʼ�ͽ����ı�־��" << endl;
    cin >> a;
    if (a != '#')
    {
        cout << "����#��Ϊ��ʼ��־��" << endl;
        exit(2);
    }
    cin >> a;
    //aprior = a;
    string temp;
    vector<string> expression_vec;
    vector<string> back_expression_vec;
    //#6+15*(21-8/4)#
    
    while (a != '#')
    {
        if (((a >= '0') && (a <= '9'))||(a == '.'))
        {
            temp += a;
        }
        else if((a == '+')|| (a == '-')|| (a == '*')|| (a == '/')|| (a == '(')|| (a == ')'))
        {
            if (temp != "")
            {
                expression_vec.push_back(temp);
            }
            
            temp = a;
            expression_vec.push_back(temp);
            temp = "";
        }
        else
        {
            cout << "������Ϸ��ַ���" << a << "���ǺϷ��ַ���" << endl;
            exit(1);
        }
        //aprior = a;
        cin >> a;
        
    }
    if (temp != "")
    {
        expression_vec.push_back(temp);
    }
    if (!Check(expression_vec))
    {
        exit(1);
    }
    TurnBack(expression_vec, back_expression_vec);
    cout << "�ñ��ʽ��Ӧ�ĺ�׺���ʽ�ǣ�";
    for (int i = 0; i < back_expression_vec.size(); i++)
    {
        cout << back_expression_vec[i] << " ";
    }
    cout << endl;
    int serial = 0;
    float a1;
    float b1;
    vector<string>::iterator iter;
    iter = back_expression_vec.begin();
    while (back_expression_vec.size() > 1)
    {
        if ((back_expression_vec[serial] == "+") || (back_expression_vec[serial] == "-") || (back_expression_vec[serial] == "*") || (back_expression_vec[serial] == "/"))
        {
            a1 = stringToNum<float>(back_expression_vec[serial - 2]);
            b1 = stringToNum<float>(back_expression_vec[serial - 1]);
            
            if (back_expression_vec[serial] == "+")
            {
                back_expression_vec[serial - 2] = NumToString(a1 + b1);
                iter = iter - 2;
                back_expression_vec.erase(iter + 1, iter + 3);
                serial = serial - 2;
            }
            else if (back_expression_vec[serial] == "-")
            {
                back_expression_vec[serial - 2] = NumToString(a1 - b1);
                iter = iter - 2;
                back_expression_vec.erase(iter + 1, iter + 3);
                serial = serial - 2;
            }
            else if (back_expression_vec[serial] == "*")
            {
                back_expression_vec[serial - 2] = NumToString(a1 * b1);
                iter = iter - 2;
                back_expression_vec.erase(iter + 1, iter + 3);
                serial = serial - 2;
            }
            else if (back_expression_vec[serial] == "/")
            {
                back_expression_vec[serial - 2] = NumToString(a1 / b1);
                iter = iter - 2;
                back_expression_vec.erase(iter + 1, iter + 3);
                serial = serial - 2;
            }
        }
        serial++;
        iter++;
    }
    cout << back_expression_vec[0] << endl;
}