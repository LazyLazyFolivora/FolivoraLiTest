// @author: Folivora Li
// @copyright: Folivora Li

#define _CRT_SECURE_NO_WARNINGS
/*21����3������Ӧ�� (ѡ��)������
 [��������]
����JSON (JavaScript Object Notation) ��һ�������������ݽ�����ʽ����������������ṹ�������ݡ�
  JSON ��ʽ�еĻ�����Ԫ��ֵ (value)�����ڼ򻯵�Ŀ�ı���ֻ�漰 2 �����͵�ֵ��
����* �ַ��� (string)���ַ�������˫���� " ��������һ���ַ�������Ϊ�գ���
  ����ַ����������г���˫���� "����˫����ǰ��ӷ�б�ܣ�Ҳ������ \" ��ʾ��������ַ�б�� \��
  ����������б�� \\ ��ʾ����б�ܺ��治�ܳ��� " �� \ ������ַ������磺""��"hello"��"\"\\"��
����* ���� (object)��������һ���ֵ�Ե����򼯺ϣ�����Ϊ�գ�����ֵ�Ա�ʾ��������ԣ�������������
  ֵ�����Ե����ݡ������������� { ��ʼ���һ����� } ��������ֵ��֮���Զ��� , �ָ���
  һ����ֵ�Եļ���ֵ֮����ð�� : �ָ������������ַ�����ͬһ���������м�ֵ�Եļ���������������ͬ��
  ֵ�������ַ�����Ҳ��������һ���������磺{}��{"foo": "bar"}��
  {"Mon": "weekday", "Tue": "weekday", "Sun": "weekend"}��
���������ַ����ڲ���λ�ã�����λ�ö����Բ���һ�������ո�ʹ�� JSON �ĳ��ָ������ۣ�
  Ҳ������һЩ�ط����У�����Ӱ������ʾ���������ݡ����磬������������һ�� JSON ����Ҳ����д������
  ��ʽ��
����{
����"Mon": "weekday",
����"Tue": "weekday",
����"Sun": "weekend"
����}
��������һ�� JSON ��ʽ���������ݣ��Լ����ɲ�ѯ����̷�����Щ��ѯ�Ľ����
�����ʽ
������һ�������������� n �� m���ֱ��ʾ JSON ���ݵ������Ͳ�ѯ�ĸ�����
���������� n �У�����һ�� JSON ���ݣ���֤������һ���Ϸ��� JSON ����
���������� m �У�ÿ������һ����ѯ������Ҫ��ѯ����������Ҫ�󷵻ض�Ӧ���Ե����ݡ�
  ��Ҫ֧�ֶ���ѯ�������������֮����С���� . ���ӡ���֤��ѯ�ĸ�ʽ���ǺϷ��ġ�
[����Ҫ��]
�����ʽ
�������������ÿһ����ѯ����˳�������ѯ�����ÿ�����ռһ�С�
���������ѯ�����һ���ַ���������� STRING <string>������ <string> ���ַ�����ֵ��
  �м���һ���ո�ָ���
���������ѯ�����һ����������� OBJECT������Ҫ�����������ݡ�
���������ѯ��������ڣ������ NOTEXIST��
��������
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
�������
STRING John
OBJECT
STRING NewYork
NOTEXIST
STRING "hello"
[����Ҫ��] 
��1��Ҫ����ı��ļ������룻
��2������Ŀ��ʵ����һ����ͨ��������ÿ�����ĺ��������̶������ܵ�������n�������������
���Կ���ʹ�ú����ֵܱ�ʾ���Ƚ��б�ʾ�ʹ洢��
��3���ϸ���Ҫ������������ʽ�������ݵ����롢�����ѵ��CSP�����еĸ�ʽ�������������ȷ�ԣ���
��4��ѡ����ʹ��ͼ�ν��棨���ַ���ʽ���ڳɵ����νṹ���ο�Linux�µ�tree�����
����״��ʽ��ʾ�����JSON��ʽ���ݡ�*/
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
    //���ҵ�������ŵ����÷�Χ
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
    for (int i = 0; i < n; i++) //�ļ����뵽vector��
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