// @author: Folivora Li
// @copyright Folivora Li

/*
5、地铁修建 (必做) （图）
[问题描述]
　　A市有n个交通枢纽，其中1号和n号非常重要，为了加强运输能力，A市决定在1号到n号枢纽间修建一条地铁。
　　地铁由很多段隧道组成，每段隧道连接两个交通枢纽。经过勘探，有m段隧道作为候选，两个交通枢纽之间最多
  只有一条候选的隧道，没有隧道两端连接着同一个交通枢纽。
　　现在有n家隧道施工的公司，每段候选的隧道只能由一个公司施工，每家公司施工需要的天数一致。
  而每家公司最多只能修建一条候选隧道。所有公司同时开始施工。
　　作为项目负责人，你获得了候选隧道的信息，现在你可以按自己的想法选择一部分隧道进行施工，
  请问修建整条地铁最少需要多少天。
输入格式
　　输入的第一行包含两个整数n, m，用一个空格分隔，分别表示交通枢纽的数量和候选隧道的数量。
第2行到第m+1行，每行包含三个整数a, b, c，表示枢纽a和枢纽b之间可以修建一条隧道，需要的时间为c天。
[基本要求]
输出格式
　　输出一个整数，修建整条地铁线路最少需要的天数。
样例输入
6 6
1 2 4
2 3 4
3 6 7
1 4 2
4 5 5
5 6 6
样例输出
6
样例说明
　　可以修建的线路有两种。
　　第一种经过的枢纽依次为1, 2, 3, 6，所需要的时间分别是4, 4, 7，则整条地铁线需要7天修完；
　　第二种经过的枢纽依次为1, 4, 5, 6，所需要的时间分别是2, 5, 6，则整条地铁线需要6天修完。
第二种方案所用的天数更少。*/
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
	//cout << "请输入顶点个数" << endl;
	cin >> G->vexnum;
	cin.ignore();
	//cout << "请输入弧个数" << endl;
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
		//cout << "请输入弧的起点和终点,以0为起点" << endl;
		cin >> start;
		cin.ignore();
		cin >> end;
		cin.ignore();
		//cout << "请输入权值" << endl;
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