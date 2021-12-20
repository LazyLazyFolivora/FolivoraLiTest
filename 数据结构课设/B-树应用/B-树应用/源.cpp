#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
typedef int Elemtype;
struct LinkNode;
struct BTreeNode;
struct LinkNode {
	LinkNode* prior = NULL;
	LinkNode* next = NULL;
	Elemtype data;
	LinkNode* leftNode = NULL;
	LinkNode* rightNode = NULL;
	struct BTreeNode* vec = NULL;
};

struct BTreeNode{
	struct LinkNode* Treenode;
	BTreeNode* PreTreenode = NULL;
	int num = 0;
};
typedef struct QueueNode {
	BTreeNode* data;
	QueueNode* next;
}QueueNode;
typedef struct {
	QueueNode* front;
	QueueNode* rear;
}LinkQueue;

void InitQueue(LinkQueue& Q)
{
	Q.front = Q.rear = new QueueNode;
	if (!Q.front)
	{
		exit(1);
	}
	Q.front->next = NULL;
}
void EnQueue(LinkQueue& Q, BTreeNode* e)
{
	QueueNode* q = new QueueNode;
	q->data = e;
	q->next = NULL;
	Q.rear->next = q;
	Q.rear = q;


}

bool QueueEmpty(LinkQueue Q)
{
	if (Q.front == Q.rear)
	{
		return true;
	}
	return false;
}
void DeQueue(LinkQueue& Q, BTreeNode*& e)
{
	if (Q.front == Q.rear)
	{
		return;
	}
	QueueNode* q;
	q = Q.front->next;
	Q.front->next = q->next;
	e = q->data;
	if (q == Q.rear)
	{
		Q.rear = Q.front;
	}
	delete q;
}
void QueueFirst(LinkQueue Q, BTreeNode*& e)
{
	if (Q.front->next != NULL)
	{
		e = Q.front->next->data;
	}
	else
	{
		e = NULL;
	}
	
}

bool IsLeaf(BTreeNode* point)
{
	LinkNode* p = point->Treenode;
	while (p != NULL)
	{
		if (p->leftNode != NULL)
		{
			return false;
		}
		if (p->rightNode != NULL)
		{
			return false;
		}
		p = p->next;
	}
	return true;
}
void ReadFile(vector<int>& number_vec)
{
	fstream file;
	file.open("D:\\BTreeData.txt", ios::in);
	if (file.fail())
	{
		cout << "error" << endl;
		exit(1);
	}
	int a;
	while (!file.eof())
	{
		file >> a;
		number_vec.push_back(a);
	}
	for (int i = 0; i < number_vec.size(); i++)
	{
		cout << number_vec[i] << "  ";
	}
}
 
void Insert(BTreeNode*& root,int maxorder,Elemtype data)
{
	if (IsLeaf(root))
	{
		LinkNode* p = new LinkNode;
		p->data = data;
		p->leftNode = NULL;
		p->rightNode = NULL;
		p->next = NULL;
		p->prior = NULL;
		p->vec = root;
		LinkNode* p1 = root->Treenode;
		if (p1 == NULL)
		{
			p1 = p;
			root->num++;
			root->Treenode = p1;
			return;
		}
		if (p1->next == NULL)
		{
			if (p1->data < p->data)
			{
				p1->next = p;
				p->prior = p1;
				p1->prior = NULL;
				root->num++;
			}
			else
			{
				p->next = p1;
				p1->prior = p;
				p1->next = NULL;
				root->num++;
			}
			return;
		}
		while (p1->next != NULL) //找到同节点该插入的位置
		{
			if (p1->data < p->data)
			{
				p1 = p1->next;
			}
			else
			{
				break;
			}
		}
		if ((p1->next == NULL) && (p1->data < p->data))
		{
			p1->next = p;
			p->prior = p1;
			root->num++;
		}
		else
		{
			p->prior = p1->prior;
			p1->prior->next = p;
			p->next = p1;
			p1->prior = p;
			root->num++;
			if (p->prior == NULL)
			{
				root->Treenode = p;
			}
		}
		if (root->num >= maxorder)//默认为3阶以上的树
		{
			int num = maxorder / 2;
			p = root->Treenode;
			for (int i = 0; i < num - 1; i++)
			{
				p = p->next;
			}
			
			LinkNode* mid = p->next;
			LinkNode* pcopy = p->next->next;
			BTreeNode* t = new BTreeNode;
			t->PreTreenode = NULL;
			t->Treenode = mid;
			t->num = 1;
			p->next = NULL;
			BTreeNode* t1 = new BTreeNode;
			pcopy->prior = NULL;
			mid->next = NULL;
			mid->prior = NULL;
			p = root->Treenode;
			t1->PreTreenode = t;
			t1->num = maxorder / 2;
			t1->Treenode = p;
			BTreeNode* t2 = new BTreeNode;
			t2->PreTreenode = t;
			t2->num = maxorder - 1 - maxorder / 2;
			t2->Treenode = pcopy;
			mid->leftNode = p;
			mid->rightNode = pcopy;
			mid->vec = t;
			root = t;
			for (int i = 0; i < num; i++)
			{
				p->vec = t1;
				p = p->next;
			}
			for (int i = 0; i < maxorder - num - 1; i++)
			{
				pcopy->vec = t2;
				pcopy = pcopy->next;
			}
		}
	}
	else
	{
		BTreeNode* t = root;
		LinkNode* p = t->Treenode;

		while (!IsLeaf(p->vec))
		{
			while (p->next != NULL)
			{
				if (data > p->data)
				{
					p = p->next;
				}
				else
				{
					break;
				}
			}
			if (data > p->data)
			{
				p = p->rightNode;
			}
			else
			{
				p = p->leftNode;
			}

		}
		LinkNode* temp1 = p;
		LinkNode* q = new LinkNode;
		q->data = data;
		q->leftNode = NULL;
		q->rightNode = NULL;
		q->prior = NULL;
		q->next = NULL;
		q->vec = p->vec;
		while (p->next != NULL)
		{
			if (p->data < q->data)
			{
				p = p->next;
			}
			else
			{
				break;
			}
		}
		if ((p->next == NULL) && (p->data < q->data))
		{
			p->next = q;
			q->prior = p;
			p->vec->num++;
		}
		else
		{
			q->prior = p->prior;
			p->prior->next = q;
			q->next = p;
			p->prior = q;
			p->vec->num++;
			if (q->prior == NULL)
			{
				temp1 = q;
				q->vec->PreTreenode->Treenode = q;
			}
		}
		q = temp1;
		while (q->vec->num >= maxorder)
		{
			
			int num = maxorder / 2;
			for (int i = 0; i < num - 1; i++)
			{
				q = q->next;
			}
			LinkNode* mid = q->next;
			LinkNode* qcopy = q->next->next;
			q->next = NULL;
			qcopy->prior = NULL;
			mid->next = NULL;
			q = temp1;
			BTreeNode* T = p->vec->PreTreenode;
			if (T == NULL)
			{
				mid->prior = NULL;
				mid->vec = p->vec;
				mid->vec->num = 1;
				mid->vec->Treenode = mid;
				mid->leftNode = q;
				mid->rightNode = qcopy;
				BTreeNode* t1 = new BTreeNode;
				t1->num = num;
				t1->PreTreenode = mid->vec;
				t1->Treenode = q;
				BTreeNode* t2 = new BTreeNode;
				t2->num = maxorder - 1 - num;
				t2->PreTreenode = mid->vec;
				t2->Treenode = qcopy;
				while (q != NULL)
				{
					q->vec = t1;
					if (q->leftNode != NULL)
					{
						q->leftNode->vec->PreTreenode = t1;
					}
					if (q->rightNode != NULL)
					{
						q->rightNode->vec->PreTreenode = t1;
					}
					q = q->next;
				}
				while (qcopy != NULL)
				{
					qcopy->vec = t2;
					if (qcopy->leftNode != NULL)
					{
						qcopy->leftNode->vec->PreTreenode = t2;
					}
					if (qcopy->rightNode != NULL)
					{
						qcopy->rightNode->vec->PreTreenode = t2;
					}
					qcopy = qcopy->next;
				}
				root = mid->vec;
				break;
			}
			else
			{
				LinkNode* q1 = T->Treenode;
				mid->vec = q1->vec;
				while (q1->next != NULL)
				{
					if (mid->data > q1->data)
					{
						q1 = q1->next;
					}
					else
					{
						break;
					}

				}
				if ((q1->next == NULL) && (mid->data > q1->data))
				{
					q1->next = mid;
					mid->prior = q1;
					q1->rightNode = q;
					mid->leftNode = q;
					mid->rightNode = qcopy;
					q1->vec->num++;
				}
				else             //插在左边
				{
					mid->prior = q1->prior;
					if (mid->prior != NULL)
					{
						mid->prior->next = mid;
					}
					mid->next = q1;
					q1->prior = mid;
					mid->leftNode = q;
					mid->rightNode = qcopy;
					q1->leftNode = q;
					q1->vec->num++;
					if (mid->prior == NULL)
					{
						q1 = mid;
						q1->vec->Treenode = q1;
					}
				}
				BTreeNode* t1 = new BTreeNode;
				t1->num = num;
				t1->PreTreenode = q1->vec;
				t1->Treenode = q;
				//t1->Treenode->leftNode->vec->PreTreenode = t1;
				//t1->Treenode->rightNode->vec->PreTreenode = t1;
				BTreeNode* t2 = new BTreeNode;
				t2->num = maxorder - 1 - num;
				t2->PreTreenode = q1->vec;
				t2->Treenode = qcopy;
				//t2->Treenode->leftNode->vec->PreTreenode = t2;
				//t2->Treenode->rightNode->vec->PreTreenode = t2;
				while (q != NULL)
				{
					q->vec = t1;
					if (q->leftNode != NULL)
					{
						q->leftNode->vec->PreTreenode = t1;
					}
					if (q->rightNode != NULL)
					{
						q->rightNode->vec->PreTreenode = t1;
					}
					q = q->next;
				}
				while (qcopy != NULL)
				{
					qcopy->vec = t2;
					if (qcopy->leftNode != NULL)
					{
						qcopy->leftNode->vec->PreTreenode = t2;
					}
					if (qcopy->rightNode != NULL)
					{
						qcopy->rightNode->vec->PreTreenode = t2;
					}
					qcopy = qcopy->next;
				}
				q = mid->vec->Treenode;
				temp1 = q;
				p = q;
			}
			
		}
	}
	

}
BTreeNode* CreateBTree(vector<Elemtype> number_vec,int& level)
{
	cout << "请输入树的阶数" << endl;
	cin >> level;
	cin.ignore();
	BTreeNode* root = new BTreeNode;
	root->PreTreenode = NULL;
	root->Treenode = NULL;
	for (int i = 0; i < number_vec.size(); i++)
	{
		Insert(root, level, number_vec[i]);
	}
	return root;
}

void Search(LinkNode*& p, BTreeNode*& root, Elemtype data)
{
	if (IsLeaf(root))
	{
		LinkNode* s = root->Treenode;
		while (s != NULL)
		{
			if (s->data == data)
			{
				p = s;
				return;
			}
			else
			{
				s = s->next;
			}
		}
	}
	else
	{
		if (p != NULL)
		{
			return;
		}
		LinkNode* q = root->Treenode;
		while (q != NULL)
		{
			if (q->data == data)
			{
				p = q;
				return;
			}
			Search(p, q->leftNode->vec, data);
			if (p != NULL)
			{
				return;
			}
			Search(p, q->rightNode->vec, data);
			if (p != NULL)
			{
				return;
			}
			q = q->next;
		}
		
	}
}

int Judge(LinkNode* p)
{
	LinkNode* pre = p->vec->PreTreenode->Treenode;
	if (p->data < pre->data)//叶子头结点
	{
		return 0;
	}
	else
	{
		while (pre->next != NULL)
		{
			pre = pre->next;
		}
		if (pre->data < p->data)//叶子尾节点
		{
			return 1;

		}
		else//非头非尾
		{
			return 2;
		}
	}
}
void Delete(BTreeNode*& root, int maxorder, Elemtype data)
{
	LinkNode* p = NULL;
	Search(p, root, data);
	if (p == NULL)
	{
		cout << "树中没有此元素!" << endl;
		return;
	}
	if (!IsLeaf(p->vec))		//若删除的不是叶子节点，把删除的值换到叶子节点上去
	{

		LinkNode* p1 = p;
		p1 = p1->leftNode;
		while (!IsLeaf(p1->vec))
		{
			while (p1->next != NULL)
			{
				p1 = p1->next;
			}
			p1 = p1->rightNode;
		}
		while (p1->next != NULL)
		{
			p1 = p1->next;
		}
		p->data = p1->data;
		p1->data = p1->data - 1;//反正这个节点是要删的，换了也没意义
		p = p1;
	}
	if (p->vec->num > maxorder / 2)			//本节点富裕
	{
		if (p->prior == NULL)		
		{
			BTreeNode* b1 = p->vec->PreTreenode;
			LinkNode* q1 = b1->Treenode;
			while ((q1->data < p->data) && (q1->next != NULL))
			{
				q1 = q1->next;
			}
			if ((q1->data < p->data) && (q1->next == NULL))
			{
				q1->rightNode = p->next;
				LinkNode* t = p;
				p->next->prior = NULL;
				p->next = NULL;
				p->prior = NULL;
				delete p;
			}
			else
			{
				q1->leftNode = p->next;
				LinkNode* t = p;
				p->next->prior = NULL;
				p->next = NULL;
				p->prior = NULL;
				p->vec->num--;
				delete p;
			}
		}
		else
		{
			LinkNode* t = p;
			p->prior->next = p->next;
			if (p->next != NULL)
			{
				p->next->prior = p->prior;
			}
			
			p->prior = NULL;
			p->next = NULL;
			p->vec->num--;
			delete p;
		}
	}
	else			//本节点不富裕
	{
		while (p->vec->PreTreenode != NULL)
		{
			if (Judge(p) == 0)//叶子头结点
			{
				LinkNode* pre = p->vec->PreTreenode->Treenode;
				LinkNode* brother = pre->rightNode;
				if (brother->vec->num > maxorder / 2)
				{
					while (p->next != NULL)
					{
						p->data = p->next->data;
						p = p->next;
					}
					p->next->data = pre->data;
					pre->data = brother->data;
					while (brother->next != NULL)
					{
						brother->data = brother->next->data;
						brother = brother->next;
					}
					brother->prior->next = NULL;
					brother->vec->num--;
					delete brother;
					return;

				}
				else           //没有富裕
				{
					LinkNode* pcopy = p;
					while (pcopy->next != NULL)
					{
						pcopy->data = pcopy->next->data;
						pcopy = pcopy->next;
					}
					pcopy->data = pre->data;
					pcopy->next = pre->rightNode;
					pcopy->next->prior = pre->prior;
					if (pcopy->prior != NULL)
					{
						pcopy->prior->rightNode = pcopy->rightNode;;
					}
					pcopy->leftNode = pcopy->rightNode;
					pcopy->rightNode = pcopy->next->leftNode;
					pcopy->next->leftNode = pcopy->rightNode;
					if (pre->vec->PreTreenode == NULL)
					{
						delete pre->vec;
						root = pcopy->vec;
						root->PreTreenode = NULL;
						return;
					}
					if (pre->vec->num > maxorder / 2)
					{
						pre->vec->PreTreenode->Treenode = pre->next;
						pre->vec->num--;
						delete pre;
						return;
					}
					else
					{
						p = pre;
					}
				}
			}
			else if (Judge(p) == 1)		//叶子尾节点
			{
				LinkNode* pre = p->vec->PreTreenode->Treenode;
				while (pre->next != NULL)
				{
					pre = pre->next;
				}
				LinkNode* brother = pre->leftNode;
				if (brother->vec->num > maxorder / 2)
				{
					while (p->prior != NULL)
					{
						p->data = p->prior->data;
						p = p->prior;
					}
					p->data = pre->data;

					while (brother->next != NULL)
					{
						brother = brother->next;
					}
					pre->data = brother->data;
					brother->prior->next = NULL;
					brother->vec->num--;
					delete brother;
					return;
				}
				else
				{
					LinkNode* pcopy = p;
					while (pcopy->prior != NULL)
					{
						pcopy->data = pcopy->prior->data;
						pcopy = pcopy->prior;
					}
					pcopy->data = pre->data;
					LinkNode* brothercopy = brother;
					while (brother->next != NULL)
					{
						brother = brother->next;
					}
					brother->next = pcopy;
					pcopy->prior = brother;
					if (pcopy->next != NULL)
					{
						pcopy->next->leftNode = pcopy->leftNode;
					}
					pcopy->rightNode = pcopy->leftNode;
					pcopy->leftNode = brother->rightNode;
					brother->rightNode = pcopy->leftNode;
					brothercopy->vec->Treenode = brothercopy;
					brother = brothercopy;
					while (brother != NULL)
					{
						brother->vec = brothercopy->vec;
						brother = brother->next;
					}
					if (pre->vec->PreTreenode == NULL)
					{
						delete pre->vec;
						root = brothercopy->vec;
						root->PreTreenode = NULL;
						return;
					}
					if (pre->vec->num > maxorder / 2)
					{
						pre->vec->num--;
						delete pre;
						return;
					}
					else
					{
						p = pre;
					}
				}
			}
			else            //非头非尾节点
			{
				LinkNode* pre = p->vec->PreTreenode->Treenode;
				while (pre->data < p->data)
				{
					pre = pre->next;
				}
				//先找左兄弟
				LinkNode* l = pre->prior->leftNode;
				LinkNode* r = pre->rightNode;
				if (l->vec->num > maxorder / 2)
				{
					while (p->prior != NULL)
					{
						p->data = p->prior->data;
						p = p->prior;
					}
					p->data = pre->prior->data;
					while (l->next != NULL)
					{
						l = l->next;
					}
					pre->data = l->data;
					l->prior->next = NULL;
					l->vec->num--;
					delete l;
					return;
				}
				else if (r->vec->num > maxorder / 2)
				{
					while (p->next != NULL)
					{
						p->data = p->next->data;
						p = p->next;
					}
					p->data = pre->data;
					pre->data = r->data;
					while (r->next != NULL)
					{
						r->data = r->next->data;
						r = r->next;
					}
					r->prior->next = NULL;
					r->vec->num--;
					delete r;
					return;
				}
				else  //都没有富裕
				{
					LinkNode* pcopy = p;
					while (pcopy->next != NULL)
					{
						pcopy->data = pcopy->next->data;
						pcopy = pcopy->next;
					}
					pcopy->data = pre->data;
					pcopy->next = pre->rightNode;
					pcopy->next->prior = pre->prior;
					pcopy->rightNode = pcopy->next->leftNode;
					pcopy->next->leftNode = pcopy->rightNode;
					if (pre->vec->num > maxorder / 2)
					{
						pre->vec->PreTreenode->Treenode = pre->next;
						pre->vec->num--;
						delete pre;
						return;
					}
					else
					{
						p = pre;
					}
				}
			}
		}
		
		
		
	}

}
void LevelTraverse(BTreeNode* root)
{
	LinkQueue q;
	InitQueue(q);
	EnQueue(q, root);
	LinkNode* p = root->Treenode;
	
	BTreeNode* e = new BTreeNode;
	while (!QueueEmpty(q))
	{
		if (p->leftNode != NULL)
		{
			EnQueue(q, p->leftNode->vec);
		}
		while (p != NULL)
		{
			if (p->rightNode != NULL)
			{
				EnQueue(q, p->rightNode->vec);
			}
			p = p->next;
		}
		DeQueue(q, e);
		while (e->Treenode != NULL)
		{
			cout << e->Treenode->data << "  ";
			e->Treenode = e->Treenode->next;
		}
		cout << endl;
		QueueFirst(q, e);
		if (e == NULL)
		{
			break;
		}
		p = e->Treenode;
	}
	

}
int main()
{
	vector<Elemtype> number_vec;
	ReadFile(number_vec);
	int level;
	BTreeNode* root = CreateBTree(number_vec, level);
	Delete(root, level, 13);
	LevelTraverse(root);
}