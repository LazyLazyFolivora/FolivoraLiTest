// @author: Folivora Li
// @copyright: Folivora Li

#define _CRT_SECURE_NO_WARNINGS
/*21、【3】树的应用 (选做)（树）
 [问题描述]
　　JSON (JavaScript Object Notation) 是一种轻量级的数据交换格式，可以用来描述半结构化的数据。
  JSON 格式中的基本单元是值 (value)，出于简化的目的本题只涉及 2 种类型的值：
　　* 字符串 (string)：字符串是由双引号 " 括起来的一组字符（可以为空）。
  如果字符串的内容中出现双引号 "，在双引号前面加反斜杠，也就是用 \" 表示；如果出现反斜杠 \，
  则用两个反斜杠 \\ 表示。反斜杠后面不能出现 " 和 \ 以外的字符。例如：""、"hello"、"\"\\"。
　　* 对象 (object)：对象是一组键值对的无序集合（可以为空）。键值对表示对象的属性，键是属性名，
  值是属性的内容。对象以左花括号 { 开始，右花括号 } 结束，键值对之间以逗号 , 分隔。
  一个键值对的键和值之间以冒号 : 分隔。键必须是字符串，同一个对象所有键值对的键必须两两都不相同；
  值可以是字符串，也可以是另一个对象。例如：{}、{"foo": "bar"}、
  {"Mon": "weekday", "Tue": "weekday", "Sun": "weekend"}。
　　除了字符串内部的位置，其他位置都可以插入一个或多个空格使得 JSON 的呈现更加美观，
  也可以在一些地方换行，不会影响所表示的数据内容。例如，上面举例的最后一个 JSON 数据也可以写成如下
  形式。
　　{
　　"Mon": "weekday",
　　"Tue": "weekday",
　　"Sun": "weekend"
　　}
　　给出一个 JSON 格式描述的数据，以及若干查询，编程返回这些查询的结果。
输入格式
　　第一行是两个正整数 n 和 m，分别表示 JSON 数据的行数和查询的个数。
　　接下来 n 行，描述一个 JSON 数据，保证输入是一个合法的 JSON 对象。
　　接下来 m 行，每行描述一个查询。给出要查询的属性名，要求返回对应属性的内容。
  需要支持多层查询，各层的属性名之间用小数点 . 连接。保证查询的格式都是合法的。
[基本要求]
输出格式
　　对于输入的每一个查询，按顺序输出查询结果，每个结果占一行。
　　如果查询结果是一个字符串，则输出 STRING <string>，其中 <string> 是字符串的值，
  中间用一个空格分隔。
　　如果查询结果是一个对象，则输出 OBJECT，不需要输出对象的内容。
　　如果查询结果不存在，则输出 NOTEXIST。
样例输入
10 5
{
"firstName": "Jo\:h,n",
"lastName": "Smith",
"address": {
"streetAddres}s": "2ndStreet",
"city": "NewYork",
"state": "NY"
},
"esc\\aped": "\"hello\""
}
firstName
address
address.city
address.postal
esc\aped
样例输出
STRING John
OBJECT
STRING NewYork
NOTEXIST
STRING "hello"
[基本要求] 
（1）要求从文本文件中输入；
（2）本题目其实就是一棵普通的树（即每个结点的孩子数不固定，不能单纯采用n叉树来解决），
可以考虑使用孩子兄弟表示法等进行表示和存储；
（3）严格按照要求的输入输出格式进行数据的输入、输出（训练CSP考试中的格式化输入输出的正确性）；
（4）选做：使用图形界面（或字符格式化摆成的树形结构，参考Linux下的tree命令），
以树状形式显示输入的JSON格式数据。*/
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
typedef struct treenode {
    treenode* leftchild;
    treenode* rightbrother;
    string data;
}Treenode;
void DealString(vector<char>& characters, vector<char>::iterator& iter,Treenode*& root)
{
    if ((*(iter) == '"') && (*(iter + 1) == '"'))
    {
        root->data = "";
        root->leftchild = NULL;
        root->rightbrother = NULL;
        return;
    }
    iter++;
    string temp;
    while (!((*(iter) == '"') && (*(iter - 1) != '\\')))
    {

        
        if ((*(iter) == '\\') && ((*(iter + 1) == '\\')|| (*(iter + 1) == '"')))
        {
            iter++;
        }
        temp += *iter;
        iter++;
        
    }
    root->data = temp;
    root->leftchild = NULL;
    root->rightbrother = NULL;
    iter++;

}
void DealObject(vector<char>& characters, vector<char>::iterator& iter, Treenode*& root)
{
    //先找到这个括号的作用范围
    Treenode* p = root;
    bool charinstring = false;
    int leftnum = 0;
    iter++;
    leftnum++;
    while (leftnum > 0)
    {
        if (*(iter) == ':')
        {
            p->leftchild = new Treenode;
            iter++;
            while (*(iter) == ' ')
            {
                iter++;
            }
            if ((*iter) == '"')
            {
                DealString(characters, iter, p->leftchild);
                p->rightbrother = new Treenode;
                p = p->rightbrother;
                p->leftchild = NULL;
                p->rightbrother = NULL;
            }
            else if (*(iter) == '{')
            {
                DealObject(characters, iter, p->leftchild);
                p->rightbrother = new Treenode;
                p = p->rightbrother;
                p->leftchild = NULL;
                p->rightbrother = NULL;
            }
        }
        else
        {
            p->rightbrother = new Treenode;
            if (*(iter) == ',')
            {
                iter++;
            }
            if ((*iter) == '"')
            {
                DealString(characters, iter, p);
            }
            else if (*(iter) == '{')
            {
                DealObject(characters, iter, p);
            }        
        }
        if ((*iter) == '}')
        {
            leftnum--;
            iter++;
        }
    }
}

/*
{
"firstName": "Jo/":h,n",
"lastName": "Smith",
"address": {
"streetAddres}s": "2ndStreet",
"city": "NewYork",
"state": "NY"
},
"esc\\aped": "\"hello\""
}
*/
void Print(Treenode* index)
{
    if (index == NULL)
    {
        cout << "NOTEXIST" << endl;
    }
    else
    {
        if ((index->leftchild->leftchild == NULL) && (index->leftchild->rightbrother == NULL))
        {
            cout << "STRING" << " " << index->leftchild->data << endl;
        }
        else
        {
            cout << "OBJECT" << endl;
        }
    }
}

void Findindex(Treenode*& root, Treenode*& index, bool& IsFind, vector<string>& name, vector<string>::iterator& iter1, int depth)
{
    if (root->data == *(iter1))
    {
        iter1++;
        if (iter1 == name.end())
        {
            IsFind = true;
            index = root;
            return;
        }
    }
    if ((root->leftchild != NULL) && (depth < name.size()))
    {
        Findindex(root->leftchild, index, IsFind, name, iter1, depth + 1);
        if (IsFind == true)
        {
            return;
        }
    }
    if (root->rightbrother != NULL)
    {
        Findindex(root->rightbrother, index, IsFind, name, iter1, depth);
        if (IsFind == true)
        {
            return;
        }
    }
}
int main()
{
    fstream file;
    file.open("D:\\topic21.txt", ios::in);
    if (file.fail())
    {
        cout << "error!" << endl;
        exit(1);
    }
    vector<char> characters;
    vector<char>::iterator iter;
    int n;
    int m;
    file >> n;
    file >> m;
    char* temp = new char[100];
    file.getline(temp, 100);
    for (int i = 0; i < n; i++) //文件读入到vector中
    {
        file.getline(temp, 100);
        for (int j = 0; j < strlen(temp); j++)
        {
            characters.push_back(temp[j]);
        }
    }
    iter = characters.begin();
    iter++;
    Treenode* root = new Treenode;
    root->leftchild = NULL;
    root->rightbrother = NULL;
    Treenode* p = root;
    Treenode* last = p;
    while (iter < characters.end() - 1)
    {
        if (*(iter) == ':')
        {
            p->leftchild = new Treenode;
            iter++;
            while (*(iter) == ' ')
            {
                iter++;
            }
            if ((*iter) == '"')
            {
                DealString(characters, iter, p->leftchild);
                p->rightbrother = new Treenode;
                p = p->rightbrother;
                p->leftchild = NULL;
                p->rightbrother = NULL;
            }
            else if (*(iter) == '{')
            {
                DealObject(characters, iter, p->leftchild);
                p->rightbrother = new Treenode;
                p = p->rightbrother;
                p->leftchild = NULL;
                p->rightbrother = NULL;
            }
            
        }
        else
        {
            p->rightbrother = new Treenode;
            while (*(iter) == ' ')
            {
                iter++;
            }
            if (*(iter) == ',')
            {
                iter++;

            }
            while (*(iter) == ' ')
            {
                iter++;
            }
            if ((*iter) == '"')
            {
                DealString(characters, iter, p);
                p->leftchild = NULL;
                p->rightbrother = NULL;
            }
            else if (*(iter) == '{')
            {
                DealObject(characters, iter, p);
                p->leftchild = NULL;
                p->rightbrother = NULL;
            }

        }
    }
    char** Require = new char*[m];
    for (int i = 0; i < m; i++)
    {
        Require[i] = new char[100];
        file.getline(Require[i], 100);
    }
    vector<string> name;
    vector<string>::iterator iter1;
    char sign[2] = ".";
    Treenode* index = NULL;
    bool IsFind = false;
    
    for (int i = 0; i < m; i++)
    {
        char* splitstr = strtok(Require[i], sign);
        while (splitstr)
        {
            
            name.push_back(splitstr);
            splitstr = strtok(NULL, sign);
        }
        iter1 = name.begin();
        Findindex(root, index, IsFind, name, iter1, 1);
        Print(index);
        name.clear();
        index = NULL;
        IsFind = false;
    }
    
}