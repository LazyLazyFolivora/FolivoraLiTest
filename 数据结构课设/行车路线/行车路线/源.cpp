// @author: Folivora Li
// @copyright: Folivora Li


/*16、【2】行车路线  (选做)（图）
[问题描述]
　　小明和小芳出去乡村玩，小明负责开车，小芳来导航。
　　小芳将可能的道路分为大道和小道。大道比较好走，每走1公里小明会增加1的疲劳度。小道不好走，
  如果连续走小道，小明的疲劳值会快速增加，连续走s公里小明会增加s2的疲劳度。
　　例如：有5个路口，1号路口到2号路口为小道，2号路口到3号路口为小道，3号路口到4号路口为大道
  ，4号路口到5号路口为小道，相邻路口之间的距离都是2公里。如果小明从1号路口到5号路口，
  则总疲劳值为(2+2)2+2+22=16+2+4=22。
现在小芳拿到了地图，请帮助她规划一个开车的路线，使得按这个路线开车小明的疲劳度最小。
[基本要求]
输入格式：
　　输入的第一行包含两个整数n, m，分别表示路口的数量和道路的数量。路口由1至n编号，
  小明需要开车从1号路口到n号路口。
接下来m行描述道路，每行包含四个整数t, a, b, c，表示一条类型为t，连接a与b两个路口，
长度为c公里的双向道路。其中t为0表示大道，t为1表示小道。保证1号路口和n号路口是连通的。
输出格式
输出一个整数，表示最优路线下小明的疲劳度。
样例输入
6 7
1 1 2 3
1 2 3 2
0 1 3 30
0 3 4 20
0 4 5 30
1 3 5 6
1 5 6 1
样例输出
76
样例说明
　　从1走小道到2，再走小道到3，疲劳度为52=25；然后从3走大道经过4到达5，疲劳度为20+30=50；
  最后从5走小道到6，疲劳度为1。总共为76。
课程设计要求：
（1）要求从文本文件中输入；
（2）采用适当的数据结构存储由输入数据中的道路所形成的图结构；
（3）编写尽可能优的算法，处理好连续走小道造成的疲劳值的指数增长
（提示：基于迪杰斯特拉算法进行改进即可完成本题）；
（4）除严格按题目要求进行输出以外，还要求输出最优路线的路径，
以及从出发点到各个点的最小疲劳值。*/

//可能是我理解有误，个人觉得这题不是用dijkstra做的，因为这题的边的权值不是固定的，与前一个遍历
//的边有关系，在特定情况下相当于产生了负权边，而我们知道dijkstra只能算没有负权边的最小路径
//当然还是根据要求用dijkstra写了，其实是不想改了- -
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;
const ll MAX_INF = 0x3f3f3f3f;
typedef struct {
    ll distance;
    int type;
}Road;

//0是大道,1是小道

int Min(int* a, int length, int& start, int* b)
{
    int min = a[0];
    start = 1;
    for (int i = 1; i < length + 1; i++)
    {
        if ((min > a[i]) && (b[i] == 0))
        {
            min = a[i];
            start = i;
        }
    }
    return min;
}
void Dijkstra(Road** A, int n, int start)
{
    int* a = new int[n + 1];        //存是否被访问过
    int* b = new int[n + 1];        //存最短路径值
    int min = 0;
    int lasttype = 0;
    int smallroad_dis = 0;
    int start1 = start;
    int startcopy = start;
    memset(b, MAX_INF, sizeof(int) * (n + 1));
    memset(a, 0, sizeof(int) * (n + 1));
    a[start] = 1;
    vector<int> con;
    con.push_back(start);
    int word = 0;
    for (int j = 0; j < n; j++)
    {
        for (int i = 1; i < n + 1; i++)
        {
            if ((A[start][i].type >= 0) && (a[i] == 0))
            {
                if ((A[start][i].type == 0))
                {
                    if (b[i] > min + A[start][i].distance)
                    {
                        b[i] = A[start][i].distance + min;
                    }
                }
                else if (A[start][i].type == 1)
                {
                    int temp = smallroad_dis + A[start][i].distance;
                    if (lasttype == 0)
                    {
                        if (b[i] > min + temp * temp)
                        {
                            b[i] = min + temp * temp;
                        }
                    }
                    else if (lasttype == 1)
                    {
                        int temp1 = smallroad_dis * smallroad_dis;
                        if (b[i] > min - temp1 + temp * temp)
                        {
                            b[i] = min - temp1 + temp * temp;
                        }
                    }
                    

                }
               
            }
        }
        start1 = start;
        min = Min(b, n, start, a);
        if (word == 0)
        {
            con.push_back(start);
        }
        if (start == n)
        {
            word = 1;
        }
        lasttype = A[start1][start].type;
        if (lasttype == 0)
        {
            smallroad_dis = 0;
        }
        else if (lasttype == 1)
        {
            smallroad_dis += A[start1][start].distance;
        }
        a[start] = 1;
    }
    cout << "最短路径为:";
    for (int i = 0; i < con.size() - 1; i++)
    {
        cout << con[i] << "-->";
    }
    cout << con[con.size() - 1] << endl;
    cout << "最短距离为" << b[n] << endl;
    cout << "从起点到各个点的最短距离为:";
    for (int i = 2; i < n + 1; i++)
    {
        cout << "到点" << i << ":" << b[i] << endl;
    }
}
int main()
{
    int n;
    int m;
    fstream file;
    file.open("D:\\topic16.txt", ios::in);
    if (file.fail())
    {
        cout << "error" << endl;
        exit(1);
    }
    file >> n;
    file >> m;
    Road** a = new Road * [n + 1];
    for (int i = 0; i <= n; i++)
    {
        a[i] = new Road[n + 1];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            a[i][j].distance = MAX_INF;
            a[i][j].type = -1;
        }
    }
    int type;
    int x;
    int y;
    int distance;
    for (int i = 0; i < m; i++)
    {
        file >> type;
        file >> x;
        file >> y;
        file >> distance;
        a[x][y].distance = distance;
        a[x][y].type = type;
        a[y][x].distance = distance;
        a[y][x].type = type;
    }
    Dijkstra(a, n, 1);
    file.close();
}