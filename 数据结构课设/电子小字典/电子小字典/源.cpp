/*24、【3】电子小字典（选做）（查找）
[问题描述]
利用键树结构，建立一个微型电子字典。
[基本要求]
实现生词的加入，单词的查找、删除，修改等操作。*/
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
using namespace std;
typedef struct treenode {
	char letter;
	bool IsWord = false;
	string meaning;
	treenode* next[26];
}Treenode;
void ReadFile(map<string, string>& dict)
{
	string word;
	string meaning;
	fstream file;
	file.open("D:\\dictionary.txt", ios::in);
	if (file.fail())
	{
		cout << "error!" << endl;
		exit(1);
	}
	while (!file.eof())
	{
		file >> word;
		file >> meaning;
		dict.insert(pair<string, string>(word, meaning));
	}
}
Treenode* InitTree()
{
	Treenode* root = new Treenode;
	for (int i = 0; i < 26; i++)
	{
		root->next[i] = NULL;
	}
	return root;
}
int MapLetterToNum(char letter)
{
	return int(letter) - 97;
}
void Memset(Treenode* next[26])
{
	for (int i = 0; i < 26; i++)
	{
		next[i] = NULL;
	}
}
void Insert(Treenode*& root, string word, string meaning)
{
	Treenode* p = root;
	int i = 0;
	for (i = 0; i < word.length(); i++)
	{
		
		if (p->next[MapLetterToNum(word[i])] == NULL)
		{
			p->next[MapLetterToNum(word[i])] = new Treenode;
			Memset(p->next[MapLetterToNum(word[i])]->next);
			p->next[MapLetterToNum(word[i])]->letter = word[i];
			p = p->next[MapLetterToNum(word[i])];
		}
		else
		{
			p = p->next[MapLetterToNum(word[i])];
		}
		
		
	}
	p->IsWord = true;
	p->meaning = meaning;
}
void Search(Treenode*& root, string word)
{
	Treenode* p = root;
	int i = 0;
	for (i = 0; i < word.length(); i++)
	{
		if (p->next[MapLetterToNum(word[i])] == NULL)
		{
			cout << "查找的单词不存在！" << endl;
			return;
		}
		else
		{
			p = p->next[MapLetterToNum(word[i])];
		}
	}
	cout << word << ":";
	cout << p->meaning << endl;
}
bool IsHaveBranch(Treenode* root, int serial)
{
	for (int i = 0; i < 26; i++)
	{
		if (i != serial)
		{
			if (root->next[i] != NULL)
			{
				return true;
			}
		}
	}
	return false;
}
bool Delete(Treenode*& root, string word)
{
	Treenode* p = root;
	vector<Treenode*> word_vec;
	vector<Treenode*>::iterator iter;
	int i = 0;
	for (i = 0; i < word.length(); i++)
	{
		if (p->next[MapLetterToNum(word[i])] == NULL)
		{
			cout << "查找的单词不存在！" << endl;
			return false;
		}
		else
		{
			p = p->next[MapLetterToNum(word[i])];
			word_vec.push_back(p);
		}
	}
	Treenode* pre = NULL;
	for (iter=word_vec.end() - 1; iter != word_vec.begin(); iter--)
	{
		pre = *(iter - 1);
		pre->next[MapLetterToNum((*iter)->letter)] = NULL;
		if (IsHaveBranch(pre, MapLetterToNum((*iter)->letter)))
		{
			break;
		}
	}
	return true;
}
void Modify(Treenode*& root)
{
	cout << "请输入要修改的单词：" << endl;
	string wrongword;
	cin >> wrongword;
	cin.ignore();
	cout << "请输入修改后的单词：" << endl;
	string rightword;
	cin >> rightword;
	cin.ignore();
	cout << "请输入释义：" << endl;
	string meaning;
	cin >> meaning;
	cin.ignore();
	if (Delete(root, wrongword) == true)
	{
		Insert(root, rightword, meaning);
	}
}
int main()
{
	map<string, string> dict;
	ReadFile(dict);
	Treenode* root = (InitTree());
	map<string, string>::iterator iter;
	int i = 0;
	for (iter = dict.begin(); iter != dict.end(); iter++,i++)
	{
		Insert(root, iter->first, iter->second);
	}
	Search(root, "zinc");
	Search(root, "abandon");
	//Delete(root, "abandon");
	
	Modify(root);
	Search(root, "abandon");
	Search(root, "aaqw");
}