// @author: Folivora Li
// @copyright: Folivora Li


/*20、【3】营业窗口队列模拟 (选做)（队列）
[问题描述]
实现具有n（n=3）个窗口的现实队列模拟，统计每人的等待时间。
[基本要求]
（1） 随机产生顾客的到达时间和服务时间存储文件。
（2） 利用文件数据实现队列的插入和删除。
（3）当有顾客离开时，根据队列长度调整队尾。
（4）考虑顾客中途离队的情况。
（5） 考虑顾客具有优先级的情况。*/
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
typedef struct
{
	int person;
	int arrivetime;
	int servicetime;
	int prior;
}Element;

typedef struct QueueNode {
	QueueNode* next;
	Element data;
}QueueNode;

typedef struct LinkQueue {
	QueueNode* front;
	QueueNode* rear;
};

void InitQueue(LinkQueue& q)
{
	q.front = q.rear = new QueueNode;
	q.front->next = NULL;
}

void EnQueue(LinkQueue& q, Element e)
{
	QueueNode* p = new QueueNode;
	p->data = e;
	p->next = NULL;
	q.rear->next = p;
	q.rear = p;

}

void DeQueue(LinkQueue& q, QueueNode*& head)
{
	
	QueueNode* p = q.front->next;
	if (p == NULL)
	{
		return;
	}
	q.front->next = p->next;
	head = p->next;
	cout << "：业务办理完成用户信息：" << "姓名:" << p->data.person << "  " << endl;
	if (p == q.rear)
	{
		q.rear = q.front;
	}
	p = NULL;
	delete p;
}
void QuitQueue(LinkQueue& q,Element data)
{
	QueueNode* p = q.front->next;
	QueueNode* prior = q.front;
	while (p != NULL)
	{
		if ((p->data.arrivetime == data.arrivetime) && (p->data.servicetime == data.servicetime) && (p->data.person == data.person) && (p->data.prior == data.prior))
		{
			prior->next = p->next;
			p = NULL;
			delete p;
			return;
		}
		p = p->next;
		prior = prior->next;
		
	}
}
int QueueLength(LinkQueue Q)
{
	int length = 0;
	QueueNode* q = Q.front;
	while (q->next)
	{
		length++;
		q = q->next;
	}
	return length;
}
void PriorInsert(LinkQueue& q, Element e)
{
	QueueNode* p = new QueueNode;
	p->data = e;
	QueueNode* q1 = q.front;
	if (q.front->next == NULL)
	{
		q.front->next = p;
		q.rear = p;
		p->next = NULL;
		return;
	}
	q1 = q1->next;
	while(q1->next != NULL)
	{
		if (q1->next->data.prior < e.prior)
		{
			break;
		}
		q1 = q1->next;
	}
	p->next = q1->next;
	q1->next = p;
}
bool operator<(const Element& tempa, const Element& tempb)
{
	if (tempa.arrivetime < tempb.arrivetime)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CreateFile()
{
	srand(time(NULL));
	fstream file;
	file.open("D:\\randomprior.txt", ios::out);
	if (file.fail())
	{
		cout << "error" << endl;
		exit(1);
	}
	Element e[100];
	vector<Element> vec;
	vector<Element>::iterator iter;
	
	for (int i = 0; i < 100; i++)
	{
		e[i].person = i + 1;
		e[i].arrivetime = rand() % 580 + 500;
		srand(2 * i);
		e[i].servicetime = rand() % 20 + 1;
		srand(5 * i);
		e[i].prior = rand() % 5;
		srand(time(NULL) * i);
		vec.push_back(e[i]);
	//file << person;
	//file << " ";
	//file << arrivetime;
	//file << " ";
	//file << servicetime;
	//file << " ";
	//if (prior > 0)
	//{
	//	file << 0;
	//	file << "\n";
	//}
	//else
	//{
	//	file << 1;
	//	file << "\n";
	//}

	}
	iter = vec.begin();
	
	sort(iter, vec.end());
	for (int i = 0; i < vec.size(); i++)
	{
		file << vec[i].person;
		file << " ";
		file << vec[i].arrivetime;
		file << " ";
		file << vec[i].servicetime;
		file << " ";
		if (vec[i].prior > 0)
		{
			file << 0;
			file << "\n";
		}
		else
		{
			file << 1;
			file << "\n";
		}

	}
	file.close();
}

void ReadFile(vector<Element>& vec)
{
	int person;
	int arrivetime;
	int servicetime;
	int prior;
	fstream file;
	file.open("D:\\randomprior.txt", ios::in);
	if (file.fail())
	{
		cout << "error" << endl;
		exit(1);
	}
	Element e;
	for (int i = 0; i < 100; i++)
	{
		file >> person;
		file >> arrivetime;
		file >> servicetime;
		file >> prior;
		e.arrivetime = arrivetime;
		e.person = person;
		e.prior = prior;
		e.servicetime = servicetime;
		vec.push_back(e);
	}
}

int Min(int a, int b, int c)
{
	int temp = a;
	if (temp > b)
	{
		temp = b;
	}
	if (temp > c)
	{
		temp = c;
	}
	if (temp == a)
	{
		return 1;
	}
	else if (temp == b)
	{
		return 2;
	}
	else
	{
		return 3;
	}
}
int main()
{

	int Time = 500;
	vector<Element> vec;
	ReadFile(vec);
	LinkQueue q1;
	LinkQueue q2;
	LinkQueue q3;
	InitQueue(q1);
	InitQueue(q2);
	InitQueue(q3);
	int finishtime1 = 0;
	int finishtime2 = 0;
	int finishtime3 = 0;
	int word1 = 0;
	int word2 = 0;
	int word3 = 0;
	int word11 = 0;
	int word22 = 0;
	int word33 = 0;
	int serial = 0;
	QueueNode* head = NULL;
	int hour;
	int min;
	while (Time < 1100)
	{
		hour = Time / 60;
		min = Time % 60;
		if (serial < 100)
		{
			while (vec[serial].arrivetime == Time)
			{

				if (Min(QueueLength(q1), QueueLength(q2), QueueLength(q3)) == 1)
				{
					if (vec[serial].prior == 0)
					{
						EnQueue(q1, vec[serial]);
					}
					else
					{
						PriorInsert(q1, vec[serial]);
					}
					if (word1 == 0)
					{
						word1 = 1;
						finishtime1 = vec[serial].servicetime + Time;
					}
				}
				else if (Min(QueueLength(q1), QueueLength(q2), QueueLength(q3)) == 2)
				{
					if (vec[serial].prior == 0)
					{
						EnQueue(q2, vec[serial]);
					}
					else
					{
						PriorInsert(q2, vec[serial]);
					}
					if (word2 == 0)
					{
						word2 = 1;
						finishtime2 = vec[serial].servicetime + Time;
					}
				}
				else
				{
					if (vec[serial].prior == 0)
					{
						EnQueue(q3, vec[serial]);
					}
					else
					{
						PriorInsert(q3, vec[serial]);
					}
					if (word3 == 0)
					{
						word3 = 1;
						finishtime3 = vec[serial].servicetime + Time;
					}
				}
				
				if (serial < vec.size())
				{
					serial++;
				}

				if (serial == vec.size())
				{
					break;
				}
				//cout << Time << endl;
				//cout << QueueLength(q1) << " " << QueueLength(q2) << " " << QueueLength(q3) << endl;
			}
		}
		
		if (finishtime1 == Time)
		{
			cout << "窗口1在" << hour << "时" << min << "分" << "办理业务完成";
			DeQueue(q1, head);
			if (head != NULL)
			{
				finishtime1 += head->data.servicetime;
			}
			else
			{
				finishtime1 = 0;
				word1 = 0;
			}

		}
		if (finishtime2 == Time)
		{
			cout << "窗口2在" << hour << "时" << min << "分" << "办理业务完成";
			DeQueue(q2, head);
			if (head != NULL)
			{
				finishtime2 += head->data.servicetime;
			}
			else
			{
				finishtime2 = 0;
				word2 = 0;
			}

		}
		if (finishtime3 == Time)
		{
			cout << "窗口3在" << hour << "时" << min << "分" << "办理业务完成";
			DeQueue(q3, head);
			if (head != NULL)
			{
				finishtime3 += head->data.servicetime;
			}
			else
			{
				finishtime3 = 0;
				word3 = 0;
			}
		}
		Time++;
	}


}