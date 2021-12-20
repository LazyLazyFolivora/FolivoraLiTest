// @author: Folivora Li
// @copyright: Folivora Li

/*
17、【2】算术表达式求值 (选做) （栈）
[问题描述]
　　一个算术表达式是由操作数(operand)、运算符(operator)和界限符(delimiter)组成的。
  假设操作数是正实数，运算符只含加减乘除等四种运算符，界限符有左右括号和表达式起始、结束符“#”，
  如：#6+15*（21-8/4）#。引入表达式起始、结束符是为了方便。
  编程利用“运算符优先法”求算术表达式的值。
[基本要求]
（1） 从键盘或文件读入一个合法的算术表达式，输出正确的结果。
（2） 显示输入序列和栈的变化过程。
（3） 考虑算法的健壮性，当表达式错误时，要给出错误原因的提示。
（4） 实现非整数的处*/

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
            cout << "不能将" << expression_vec[i] << "和" << expression_vec[i + 1] << "两个符号放一起" << endl;
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
    cout << "请用#作为起始和结束的标志！" << endl;
    cin >> a;
    if (a != '#')
    {
        cout << "请用#作为起始标志！" << endl;
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
            cout << "请输入合法字符，" << a << "不是合法字符！" << endl;
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
    cout << "该表达式对应的后缀表达式是：";
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