// @author: Folivora Li
// @copyright: Folivora Li


/*23、【3】平衡二叉树操作的演示（选做） （查找）
[问题描述]
利用平衡二叉树实现一个动态查找表。
[基本要求]
（1） 从文件读取数据
（2）实现动态查找表的三种基本功能：查找、插入和删除。
（3）以可验证的方式输出结果*/
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
typedef struct treenode{
	treenode* left;
	treenode* right;
	int data;
	int height;
	treenode* parent;
}Treenode;
void ReadFile(vector<int>& vec)
{
	fstream file;
	file.open("D:\\balancetree.txt", ios::in);
	if (file.fail())
	{
		cout << "error!" << endl;
		exit(1);
	}
	int data;
	while (!file.eof())
	{
		file >> data;
		vec.push_back(data);
	}
	file.close();
}

//右旋
void RightRotation(Treenode*& target)
{
	int left = 0;
	int right = 0;
	if (target->parent->left == target)
	{
		left = 1;
	}
	if (target->parent->right == target)
	{
		right = 1;
	}
	Treenode* p = target->left->right;
	Treenode* p1 = target->left;
	target->left->right = target;
	target->left = p;
	p1->parent = target->parent;
	target->parent = p1;
	if (p != NULL)
	{
		p->parent = target;
	}
	
	if (right == 1)
	{
		p1->parent->right = p1;
	}
	if (left == 1)
	{
		p1->parent->left = p1;
	}
	target = p1;
}
void FindEndNode(Treenode*& root, Treenode*& target)
{
	if (root != NULL)
	{
		target = root;
	}
	if (root->left != NULL)
	{
		FindEndNode(root->left, target);
	}
	if (root->right != NULL)
	{
		FindEndNode(root->right, target);
	}
	
}
//左旋
void LeftRotation(Treenode*& target)
{
	int left = 0;
	int right = 0;
	if (target->parent->left == target)
	{
		left = 1;
	}
	if (target->parent->right == target)
	{
		right = 1;
	}
	Treenode* p = target->right->left;
	Treenode* p1 = target->right;
	target->right->left = target;
	target->right = p;
	p1->parent = target->parent;
	target->parent = p1;
	if (p != NULL)
	{
		p->parent = target;
	}
	
	if (right == 1)
	{
		p1->parent->right = p1;
	}
	if (left == 1)
	{
		p1->parent->left = p1;
	}
	target = p1;
}
int Max(int a, int b)
{
	if (a > b)
	{
		return a;
	}
	return b;
}
void Height(Treenode* root, int& maxdepth, int depth)
{
	if (depth > maxdepth)
	{
		maxdepth = depth;
	}
	if (root->left != NULL)
	{
		Height(root->left, maxdepth, depth + 1);
	}
	if (root->right != NULL)
	{
		Height(root->right, maxdepth, depth + 1);
	}
}
void CaucaluteHeight(Treenode* root)
{
	int leftheight = 0;
	int rightheight = 0;
	if (root->left != NULL)
	{
		Height(root->left, leftheight, 1);
	}
	if (root->right != NULL)
	{
		Height(root->right, leftheight, 1);
	}
	root->height = Max(leftheight, rightheight);
	
}
void GiveHeight(Treenode*& root)
{
	CaucaluteHeight(root);
	if (root->left != NULL)
	{
		GiveHeight(root->left);
	}
	if (root->right != NULL)
	{
		GiveHeight(root->right);
	}
}
void InitTree(Treenode*& root, int data)
{
	if (root == NULL)
	{
		exit(1);
	}
	Treenode* t = new Treenode;
	t->data = data;
	t->parent = root;
	t->left = NULL;
	t->right = NULL;
	t->height = 0;
	root->left = t;
	root->right = t;
}
void FindNode(Treenode*& root, Treenode*& target, int data)
{
	if (root->data == data)
	{
		target = root;
		return;
	}
	if (root->left != NULL)
	{
		FindNode(root->left, target, data);
	}
	if (root->right != NULL)
	{
		FindNode(root->right, target, data);
	}
}
void FindUnBalanceNode(Treenode*& root, Treenode*& target)
{
	int rightheight = 0;
	int leftheight = 0;
	if (root->left != NULL)
	{
		leftheight = root->left->height + 1;
	}
	if (root->right != NULL)
	{
		rightheight = root->right->height + 1;
	}
	if (fabs(leftheight - rightheight) >= 2)
	{
		target = root;
	}
	if (root->left != NULL)
	{
		FindUnBalanceNode(root->left, target);
	}
	if (root->right != NULL)
	{
		FindUnBalanceNode(root->right, target);
	}
}
void Search(Treenode*& root, int data, bool& IsFind,int depth)
{
	if (data == root->data)
	{
		cout << data << "在第" << depth << "层中" << endl;
		IsFind = true;
		return;
	}
	if (root->left != NULL)
	{
		Search(root->left, data, IsFind, depth + 1);
	}
	if (root->right != NULL)
	{
		Search(root->right, data, IsFind, depth + 1);
	}
}
void Insert_Tree(Treenode*& root, int data)
{
	Treenode* t = new Treenode;
	t->left = NULL;
	t->right = NULL;
	t->parent = new Treenode;
	t->data = data;
	Treenode* p = root;
	Treenode* p1 = NULL;
	while (p != NULL)
	{
		p1 = p;
		if (data > p->data)
		{
			p = p->right;
		}
		else
		{
			p = p->left;
		}
	}
	if (data > p1->data)
	{
		p1->right = t;
		t->parent = p1;
	}
	else
	{
		p1->left = t;
		t->parent = p1;
	}
	GiveHeight(root);
	Treenode* ubtree = NULL;
	FindUnBalanceNode(root, ubtree);
	if (ubtree == NULL)
	{
		return;
	}
	if (data > ubtree->data)
	{
		if (data > ubtree->right->data)
		{
			LeftRotation(ubtree);
		}
		else
		{
			RightRotation(ubtree->right);
			LeftRotation(ubtree);
		}
	}
	else
	{
		if (data < ubtree->left->data)
		{
			RightRotation(ubtree);
		}
		else
		{
			LeftRotation(ubtree->left);
			RightRotation(ubtree);
		}
	}



}
void PrePrint(Treenode* root)
{
	if (root != NULL)
	{
		cout << root->data << "  ";
	}
	else
	{
		return;
	}
	if (root->left != NULL)
	{
		PrePrint(root->left);
	}
	if (root->right != NULL)
	{
		PrePrint(root->right);
	}
}
void Delete(Treenode*& root, int data)
{
	Treenode* target = NULL;
	FindNode(root, target, data);
	if (target == NULL)
	{
		cout << "树中没有此元素！" << endl;
		return;
	}
	if ((target->left == NULL) && (target->right == NULL))
	{
		if (target->parent->left == target)
		{
			target->parent->left = NULL;
		}
		else
		{
			target->parent->right = NULL;
		}
		delete target;
	}
	else if ((target->left == NULL) && (target->right != NULL))
	{
		if (target->parent->left->data == target->data)
		{
			target->parent->left = target->right;
			target->right->parent = target->parent;
			delete target;
		}
		else
		{
			target->parent->right = target->right;
			target->right->parent = target->parent;
			delete target;
		}
	}
	else if ((target->left != NULL) && (target->right == NULL))
	{
		if (target->parent->left->data == target->data)
		{
			target->parent->left = target->left;
			target->left->parent = target->parent;
			delete target;
		}
		else
		{
			target->parent->right = target->left;
			target->left->parent = target->parent;
			delete target;
		}
		return;
	}
	else
	{
		Treenode* d = NULL;
		if ((target->left->height) - (target->right->height) >= 0)	//左子树层数多
		{
			Treenode* p = target;
			p = p->left;
			while (p->right != NULL)
			{
				p = p->right;
			}
			int temp;
			temp = p->data;
			p->data = target->data;
			target->data = temp;
			d = p;
		}
		else
		{
			Treenode* p = target;
			p = p->right;
			while (p->left != NULL)
			{
				p = p->left;
			}
			int temp;
			temp = p->data;
			p->data = target->data;
			target->data = temp;
			d = p;
		}
		if ((d->left == NULL) && (d->right == NULL))
		{
			if (d->parent->left->data == d->data)
			{
				d->parent->left = NULL;
				delete d;
			}
			else
			{
				d->parent->right = NULL;
				delete d;
			}
		}
		else
		{
			if (d->left != NULL)
			{
				if (d->parent->left->data == d->data)
				{
					d->parent->left = d->left;
					delete d;
				}
				else
				{
					d->parent->right = d->left;
					delete d;
				}
			}
			else
			{
				if (d->parent->left->data == d->data)
				{
					d->parent->left = d->right;
					delete d;
				}
				else
				{
					d->parent->right = d->right;
					delete d;
				}
			}
		}
	}
	GiveHeight(root);
	Treenode* target1 = NULL;
	FindUnBalanceNode(root, target1);
	if (target1 == NULL)
	{
		return;
	}
	Treenode* crime = NULL;
	FindEndNode(target1, crime);
	if (crime->data > target1->data)
	{
		if (crime->data > target1->right->data)
		{
			LeftRotation(target1);
		}
		else
		{
			RightRotation(target1->right);
			LeftRotation(target);
		}
	}
	else
	{
		if (crime->data < target1->left->data)
		{
			RightRotation(target1);
		}
		else
		{
			LeftRotation(target1->left);
			RightRotation(target1);
		}
	}
	//if (target1->left < target1->right)
	//{
	//	if (target1->right->left->height - target1->right->right->height <= 0)
	//	{
	//		LeftRotation(root);
	//	}
	//	else
	//	{
	//		RightRotation(root->right);
	//		LeftRotation(root);
	//	}
	//}
	//else
	//{
	//	if (target1->left->left->height - target1->left->right->height >= 0)
	//	{
	//		RightRotation(root);
	//	}
	//	else
	//	{
	//		LeftRotation(root->left);
	//		RightRotation(root);
	//	}
	//}

}
int main()
{
	vector<int> vec;
	ReadFile(vec);
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << endl;
	}
	Treenode* root = new Treenode;
	InitTree(root, vec[0]);
	int i = 1;
	while (i < vec.size())
	{
		Insert_Tree(root->left, vec[i]);
		i++;
	}
	PrePrint(root->left);
	cout << endl;
	bool IsFind = false;
	Search(root->left, 9, IsFind, 1);
	if (IsFind == false)
	{
		cout << "无此元素！" << endl;
	}
	Delete(root->left, 10);
	PrePrint(root->left);
	cout << endl;
	Search(root->left, 10, IsFind, 1);
	if (IsFind == false)
	{
		cout << "无此元素！" << endl;
	}
}