// @author: Folivora Li
// @copyright Folivora Li

/*
5�������޽� (����) ��ͼ��
[��������]
����A����n����ͨ��Ŧ������1�ź�n�ŷǳ���Ҫ��Ϊ�˼�ǿ����������A�о�����1�ŵ�n����Ŧ���޽�һ��������
���������ɺܶ�������ɣ�ÿ���������������ͨ��Ŧ��������̽����m�������Ϊ��ѡ��������ͨ��Ŧ֮�����
  ֻ��һ����ѡ�������û���������������ͬһ����ͨ��Ŧ��
����������n�����ʩ���Ĺ�˾��ÿ�κ�ѡ�����ֻ����һ����˾ʩ����ÿ�ҹ�˾ʩ����Ҫ������һ�¡�
  ��ÿ�ҹ�˾���ֻ���޽�һ����ѡ��������й�˾ͬʱ��ʼʩ����
������Ϊ��Ŀ�����ˣ������˺�ѡ�������Ϣ����������԰��Լ����뷨ѡ��һ�����������ʩ����
  �����޽���������������Ҫ�����졣
�����ʽ
��������ĵ�һ�а�����������n, m����һ���ո�ָ����ֱ��ʾ��ͨ��Ŧ�������ͺ�ѡ�����������
��2�е���m+1�У�ÿ�а�����������a, b, c����ʾ��Ŧa����Ŧb֮������޽�һ���������Ҫ��ʱ��Ϊc�졣
[����Ҫ��]
�����ʽ
�������һ���������޽�����������·������Ҫ��������
��������
6 6
1 2 4
2 3 4
3 6 7
1 4 2
4 5 5
5 6 6
�������
6
����˵��
���������޽�����·�����֡�
������һ�־�������Ŧ����Ϊ1, 2, 3, 6������Ҫ��ʱ��ֱ���4, 4, 7����������������Ҫ7�����ꣻ
�����ڶ��־�������Ŧ����Ϊ1, 4, 5, 6������Ҫ��ʱ��ֱ���2, 5, 6����������������Ҫ6�����ꡣ
�ڶ��ַ������õ��������١�*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define MAX_VERTEX_NUM 20
typedef int Elemtype;
typedef char Vertextype;
typedef int** AdjMatrix;
typedef enum {
	DG, DN, UDG, UDN
}GraphKind;
typedef struct {
	Vertextype vexs[MAX_VERTEX_NUM];
	AdjMatrix arcs;
	int vexnum, arcnum;
}MGraph;

int CreateGraph(MGraph*& G)
{
	int max = 0;
	//cout << "�����붥�����" << endl;
	cin >> G->vexnum;
	cin.ignore();
	//cout << "�����뻡����" << endl;
	cin >> G->arcnum;
	cin.ignore();
	G->arcs = new int* [MAX_VERTEX_NUM];
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{

		G->arcs[i] = new int[MAX_VERTEX_NUM];

	}
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		for (int j = 0; j < MAX_VERTEX_NUM; j++)
		{
			G->arcs[i][j] = 0;
		}
	}
	int start;
	int end;
	int weight = 1;
	for (int i = 0; i < G->arcnum; i++)
	{
		//cout << "�����뻡�������յ�,��0Ϊ���" << endl;
		cin >> start;
		cin.ignore();
		cin >> end;
		cin.ignore();
		//cout << "������Ȩֵ" << endl;
		cin >> weight;
		cin.ignore();
		G->arcs[start -  1][end - 1] = weight;
		G->arcs[end - 1][start - 1] = weight;
		if (max < weight)
		{
			max = weight;
		}
	}
	return max;
}

void DFSTraverse(MGraph* G, vector<int>& Max, int last,int& max,int end,int* a )
{
	for (int i = 0; i < G->vexnum; i++)
	{
		if ((G->arcs[last][i] != 0) && (a[i] == 0))
		{
			Max.push_back(G->arcs[last][i]);
			a[i] = 1;
			if (i == end - 1)
			{
				vector<int>::iterator biggest = max_element(Max.begin(), Max.end());
				if (max > *biggest)
				{
					max = *biggest;
				}
				a[i] = 0;
				return;

			}
			DFSTraverse(G, Max, i, max, end, a);
			Max.pop_back();
			a[i] = 0;

		}
	}
}

void DFSMain(MGraph* G,int end,int max)
{
	vector<int> Max;
	int* a = new int[G->vexnum];
	memset(a, 0, sizeof(a) * G->vexnum);
	a[0] = 1;
	DFSTraverse(G, Max, 0, max, end, a);
	
	cout << max;
}

int main()
{
	MGraph* G = new MGraph;
	int max;
	max = CreateGraph(G);
	DFSMain(G, G->vexnum, max);

}