// @author: Folivora Li
// @copyright Folivora Li

/*
4、Huffman编码与解码 (必做)（Huffman编码、二叉树）
[问题描述]
对一篇不少于5000字符的英文文章（source.txt），统计各字符出现的次数，
实现Huffman编码(code.dat)，以及对编码结果的解码(recode.txt)。
[基本要求]
（1） 输出每个字符出现的次数和编码,并存储文件(Huffman.txt)。
（2） 在Huffman编码后，英文文章编码结果保存到文件中(code.dat)，
编码结果必须是二进制形式，即0 1的信息用比特位表示，不能用字符’0’和’1’表示。
（3） 实现解码功能。
*/
#include <iostream>
#include <map>
#include <fstream>
#include <string.h>
#include <stdio.h>
using namespace std;
typedef struct {
	char character;
	int time;
}Character;

typedef struct binode
{
	Character data;
	binode* left;
	binode* right;
}BiTreeNode;

BiTreeNode** CreateBiNode(Character* a, int num)
{
	BiTreeNode** treenode = new BiTreeNode * [num];
	for (int i = 0; i < num; i++)
	{
		treenode[i] = new BiTreeNode;
	}
	for (int i = 0; i < num; i++)
	{
		treenode[i]->left = NULL;
		treenode[i]->right = NULL;
		treenode[i]->data = a[i];

	}
	return treenode;
}
void CreateHuffmanTree(BiTreeNode**& treenode, int& num)
{
	BiTreeNode* min1 = treenode[0];
	BiTreeNode* min2 = treenode[1];
	int min1serial = 0;
	int min2serial = 1;
	//min1最小，min2次小
	for (int i = 1; i < num; i++)
	{
		if (min1->data.time > treenode[i]->data.time)
		{
			min1 = treenode[i];
			min1serial = i;
		}

	}
	if (min1serial == 1)
	{
		min2 = treenode[0];
		min2serial = 0;
	}
	for (int i = 0; i < num; i++)
	{
		if (min2->data.time > treenode[i]->data.time)
		{
			if (i != min1serial)
			{
				min2 = treenode[i];
				min2serial = i;
			}
		}
	}
	//两树合成
	BiTreeNode* newtreenode = new BiTreeNode;
	newtreenode->data.time = min1->data.time + min2->data.time;
	newtreenode->data.character = ' ';
	newtreenode->left = min1;
	newtreenode->right = min2;
	treenode[min1serial] = newtreenode;
	BiTreeNode* temp = treenode[min2serial];
	treenode[min2serial] = treenode[num - 1];
	num--;
	//cout << min1serial << " " << min2serial << " " << endl;


}


BiTreeNode* ReturnHuffmanTree(BiTreeNode**& treenode, int num)
{
	while (num > 1)
	{
		CreateHuffmanTree(treenode, num);
	}
	return treenode[0];
}
void PreOrderTraverse(BiTreeNode* root)
{
	if (root == NULL)
	{
		return;
	}
	cout << root->data.character << "  ";
	if (root->left != NULL)
	{
		PreOrderTraverse(root->left);
	}
	if (root->right != NULL)
	{
		PreOrderTraverse(root->right);
	}
}
void Encode(BiTreeNode* root,int* a, int length)
{
	if (root == NULL)
	{
		return;
	}
	if ((root->left == NULL) && (root->right == NULL))
	{
		fstream file;
		file.open("D:\\code.dat", ios::app|ios::out);
		cout << root->data.character << "的编码是:";
		for (int i = 0; i <length; i++)
		{
			cout << a[i];
			file << a[i];
		}
		file.close();
		cout << endl;
		return;

	}
	if (root->left != NULL)
	{
		a[length] = 0;
		Encode(root->left, a, length + 1);
	}
	if (root->right != NULL)
	{
		a[length] = 1;
		Encode(root->right, a, length + 1);
	}
}

void Decode(BiTreeNode* root,BiTreeNode* Trueroot, char* a, int length,int serial,fstream& file,int& judge)
{
	if (judge == 1)
	{
		return;
	}
	if ((root->left == NULL) && (root->right == NULL))
	{
		cout << "解码后的字符是:" << root->data.character << endl;
		file << "解码后的字符是:";
		file << root->data.character;
		file << '\n';
		if (length - 1 > serial)
		{
			Decode(Trueroot, Trueroot, a, length, serial, file, judge);
		}
		else
		{
			judge = 1;
			return;
		}

	}
	if (a[serial] == '0')
	{
		if (judge == 1)
		{
			return;
		}
		cout << 0;
		file << '0';
		Decode(root->left, Trueroot, a, length, serial + 1, file, judge);
		if (judge == 1)
		{
			return;
		}
	}
	if (a[serial] == '1')
	{
		if (judge == 1)
		{
			return;
		}
		cout << 1;
		file << '1';
		Decode(root->right, Trueroot, a, length, serial + 1, file, judge);
		if (judge == 1)
		{
			return;
		}
	}
}
int main()
{
	fstream file1;
	file1.open("D:\\source.txt", ios::in);
	if (file1.fail())
	{
		cout << "error" << endl;
		exit(1);
	}
	map<char, int>mapHuffman;
	map<char, int>::iterator iter;
	map<char, int>::iterator iter1;
	char name;
	int num = 0;
	while (!file1.eof())
	{
		file1 >> name;
		iter = mapHuffman.find(name);
		if (iter == mapHuffman.end())
		{
			mapHuffman.insert(pair<char, int>(name, 0));
			num++;
		}
		else
		{
			iter->second++;
		}
	}
	file1.close();
	for (iter1 = mapHuffman.begin(); iter1 != mapHuffman.end(); iter1++)
	{
		cout << iter1->first << ":" << iter1->second << endl;
	}
	Character* Container = new Character[num];
	int i = 0;
	for (iter = mapHuffman.begin(); iter != mapHuffman.end(); iter++, i++)
	{
		Container[i].character = iter->first;
		Container[i].time = iter->second;
	}
	BiTreeNode** treenode = CreateBiNode(Container, num);
	BiTreeNode* huffmantree = ReturnHuffmanTree(treenode, num);
	
	//PreOrderTraverse(huffmantree);
	int* a = new int[20];
	Encode(huffmantree, a, 0);
	char b[5000];
	fstream file2;
	file2.open("D:\\code.dat", ios::in);
	if (file2.fail())
	{
		cout << "error" << endl;
		exit(1);
	}
	int count = 0;
	char c;
	while (!file2.eof())
	{
		file2 >> c;
		b[count++] = c;
	}
	fstream file;
	file.open("D:\\decode.txt", ios::out);
	int judge = 0;
	Decode(huffmantree, huffmantree, b, count, 0, file,judge);
	remove("D:\\code.dat");
}