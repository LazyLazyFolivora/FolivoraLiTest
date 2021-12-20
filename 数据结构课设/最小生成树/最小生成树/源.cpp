// @author: Folivora Li
// @copyright: Folivora Li

/*22、【3】最小生成树 (选做) （图）
[问题描述]
利用普利姆算法和克鲁斯卡尔算法实现最小生成树问题。
[基本要求]
（1）自行建立图的数据文件，第一行是顶点个数，然后依次是顶点名，接下来是边，
用float表示边的权值；
（2）以邻接表或者邻接矩阵表示图皆可；
（3）分别利用Prim和Kruskal算法实现最小生成树；
（4）输出最小生成树的权值之和，及所用的边。*/
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
typedef int Elemtype;
typedef float** AdjMatrix;
typedef char Vertextype;
typedef struct {
	Vertextype* vexs;
	AdjMatrix arcs;
	int vexnum, arcnum;
}MGraph;
void CreateGraph(MGraph*& G)
{
	fstream file;
	file.open("D:\\spanningtree.txt", ios::in);
	if (file.fail())
	{
		cout << "error" << endl;
		exit(1);
	}
	file >> G->vexnum;
	G->vexs = new Vertextype[G->vexnum];
	G->arcs = new float* [G->vexnum];
	for (int i = 0; i < G->vexnum; i++)
	{
		G->arcs[i] = new float[G->vexnum];
	}
	for (int i = 0; i < G->vexnum; i++)
	{
		file >> G->vexs[i];
	}
	for (int i = 0; i < G->vexnum; i++)
	{
		for (int j = 0; j < G->vexnum; j++)
		{
			G->arcs[i][j] = 0;
		}
	}
	int x;
	int y;
	float value;
	while (!file.eof())
	{
		file >> x;
		if (file.eof())
		{
			break;
		}
		file >> y;
		if (file.eof())
		{
			break;
		}
		file >> value;
		G->arcs[x][y] = value;
		G->arcs[y][x] = value;
		G->arcnum++;
	}


}
bool IsHaveCircle(MGraph* G, int y, vector<int>& circle,bool& IsHavecircle)
{
	for (int i = 0; i < G->vexnum; i++)
	{
		if ((G->arcs[y][i] > 0) && (find(circle.begin() + 1,circle.end(),i) == circle.end()))
		{
			circle.push_back(i);
			if ((circle[0] == circle[circle.size() - 1]) && (circle.size() > 3))
			{
				IsHavecircle = true;
				return true;
			}
			if ((circle[0] == circle[2]) && (circle.size() == 3))
			{
				circle.pop_back();
			}
			else
			{
				int temp = G->arcs[i][y];
				G->arcs[i][y] = 0;//不走回头路
				IsHaveCircle(G, i, circle, IsHavecircle);
				G->arcs[i][y] = temp;
			}
			
			if (IsHavecircle == true)
			{
				return true;
			}
		}
	}
	circle.pop_back();
	return false;
}
MGraph* Prim(MGraph* G)
{
	MGraph* G1 = new MGraph;
	G1->vexnum = G->vexnum;
	G1->arcnum = G1->vexnum - 1;
	G1->vexs = new Vertextype[G->vexnum];
	G1->arcs = new float* [G->vexnum];
	for (int i = 0; i < G->vexnum; i++)
	{

		G1->arcs[i] = new float[G->vexnum];
		G1->vexs[i] = G->vexs[i];

	}
	for (int i = 0; i < G->vexnum; i++)
	{
		for (int j = 0; j < G->vexnum; j++)
		{
			G1->arcs[i][j] = 0;
		}
	}
	//Prim算法
	int* vex = new int[G->vexnum];
	for (int i = 0; i < G->vexnum; i++)
	{
		vex[i] = 0;
	}

	int start = 0;
	vex[start] = 1;
	int min = -1;
	int nextserial = -1;
	int temp;
	for (int i = 0; i < G1->vexnum - 1; i++)
	{
		for (int i1 = 0; i1 < G1->vexnum; i1++)
		{
			if (vex[i1] == 1)
			{
				start = i1;
				for (int j = 0; j < G1->vexnum; j++)
				{
					if (vex[j] == 1)
					{
						continue;
					}
					if (G->arcs[start][j] != 0)
					{
						if (min < 0)
						{
							temp = start;
							min = G->arcs[start][j];
							nextserial = j;
						}
						else if (min > 0)
						{
							if (G->arcs[start][j] < min)
							{
								temp = start;
								min = G->arcs[start][j];
								nextserial = j;
							}
						}
					}
				}
			}

		}
		vex[nextserial] = 1;
		G1->arcs[temp][nextserial] = min;
		G1->arcs[nextserial][temp] = min;
		min = -1;
		nextserial = -1;
	}
	return G1;

}
MGraph* Kruskal(MGraph* G)
{
	MGraph* G1 = new MGraph;
	G1->vexnum = G->vexnum;
	G1->arcnum = G1->vexnum - 1;
	G1->vexs = new Vertextype[G1->vexnum];
	G1->arcs = new float* [G->vexnum];
	for (int i = 0; i < G->vexnum; i++)
	{

		G1->arcs[i] = new float[G->vexnum];
		G1->vexs[i] = G->vexs[i];
	}
	for (int i = 0; i < G->vexnum; i++)
	{
		for (int j = 0; j < G->vexnum; j++)
		{
			G1->arcs[i][j] = 0;
		}
	}
	//Kruskal算法
	int x = 0;
	int y = 0;
	float min = 10000;
	vector<int> circle;
	bool IsHavecircle = false;
	for (int i = 0; i < G->vexnum - 1; i++)
	{
		for (int j = 0; j < G->vexnum; j++)
		{
			for (int k = 0; k < G->vexnum; k++)
			{
				if (G->arcs[j][k] > 0)
				{
					if (min > G->arcs[j][k])
					{
						min = G->arcs[j][k];
						x = j;
						y = k;
					}
				}
			}
		}
		G1->arcs[x][y] = min;
		G1->arcs[y][x] = min;
		circle.push_back(x);
		circle.push_back(y);
		if (!IsHaveCircle(G1, y, circle, IsHavecircle))
		{

		}
		else
		{
			G1->arcs[x][y] = 0;
			G1->arcs[y][x] = 0;
			i--;
		}
		circle.clear();
		G->arcs[x][y] = 0;
		G->arcs[y][x] = 0;
		IsHavecircle = false;
		min = 10000;
		x = -1;
		y = -1;
	}
	return G1;
}
void Give(MGraph* G, MGraph*& G1)
{
	G1->vexnum = G->vexnum;
	G1->arcnum = G->arcnum;
	G1->vexs = new Vertextype[G->vexnum];
	G1->arcs = new float* [G->vexnum];
	for (int i = 0; i < G->vexnum; i++)
	{
		G1->arcs[i] = new float[G->vexnum];
	}
	for (int i = 0; i < G->vexnum; i++)
	{
		G1->vexs[i] = G->vexs[i];
	}
	for (int i = 0; i < G->vexnum; i++)
	{
		for (int j = 0; j < G->vexnum; j++)
		{
			G1->arcs[i][j] = G->arcs[i][j];
		}
	}
}
int main()
{
	MGraph* G = new MGraph;
	CreateGraph(G);
	MGraph* G1 = new MGraph;
	Give(G, G1);
	MGraph* G2 = Prim(G1);
	float total = 0;
	cout << "Prim算法生成树的边有：" << endl;
	for (int i = 0; i < G2->vexnum; i++)
	{
		for (int j = 0; j < G2->vexnum; j++)
		{
			if (G2->arcs[i][j] != 0)
			{
				cout << G2->vexs[i] << "到" << G2->vexs[j] << " ," << "权值为" << G2->arcs[i][j] << endl;
				G2->arcs[j][i] = 0;
				total = total + G2->arcs[i][j];
			}
		}
	}
	cout << "最小权值和为：" << total << endl;
	G2 = Kruskal(G1);
	total = 0;
	cout << "Kruskal算法生成树的边有：" << endl;
	for (int i = 0; i < G2->vexnum; i++)
	{
		for (int j = 0; j < G2->vexnum; j++)
		{
			if (G2->arcs[i][j] != 0)
			{
				cout << G2->vexs[i] << "到" << G2->vexs[j] << " ," << "权值为" << G2->arcs[i][j] << endl;
				G2->arcs[j][i] = 0;
				total = total + G2->arcs[i][j];
			}
		}
	}
	cout << "最小权值和为：" << total << endl;
	
}