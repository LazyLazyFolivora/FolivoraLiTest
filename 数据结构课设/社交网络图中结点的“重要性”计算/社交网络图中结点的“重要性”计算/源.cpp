// @author: Folivora Li
// @copyright: Folivora Li

/*10、【1】 社交网络图中结点的“重要性”计算（选做）（图）
[问题描述]
在社交网络中，个人或单位（结点）之间通过某些关系（边）联系起来。他们受到这些关系的影响，
这种影响可以理解为网络中相互连接的结点之间蔓延的一种相互作用，可以增强也可以减弱。
而结点根据其所处的位置不同，在网络中体现的重要性也不尽相同。
“紧密度中心性”是用来衡量一个结点达到其他结点的“快慢”的指标，即一个有较高中心性的结点比
有较低中心性的结点能够更快地（平均意义下）到达网络中的其他结点，因而在该网络的传播过程中有
更重要的价值。在有N个结点的网络中，结点vi的“紧密度中心性” 数学上定义为 到其余所有结点(j!=i)
的最短距离的平均值的倒数：

对于非连通图，所有结点的紧密度中心性都是0。
本实验给定一个无权的无向图以及其中的一组结点，要求计算这组结点中每个结点的紧密度中心性。

[基本要求]
（1）输入说明：输入的第一行给出两个正整数N (N<=1000)和M，其中N是图中结点个数，结点编号从1到N；
M（M<=10000）是边的数目。随后的M行中，每行给出一条边的信息，即该边连接的两个结点编号，
中间用空格分隔。最后一行给出需要计算紧密度中心性的这组结点的个数K（K<=100），以及K个结点的编号，
用空格分隔。
（2）输出说明：按照“Cc(i)=x.xx”的格式输出K个给定结点的紧密度中心性，每个输出占一行，
结果精确到小数点后2位。 
（3）测试用例： 
输入  5 8
      1 2
      1 3
      1 4
      2 3
      3 4
      4 5
      2 5
      3 5
      2 4 3
输出  Cc(4) = 0.80
      Cc(3) = 1.00*/
#include <iostream>
#include <iomanip>
using namespace std;
typedef struct {
    int num;
    bool IsSigned = false;
}Array;
int Min(Array* a, int length, int& start, int* b)
{
    int min = a[0].num;
    start = 1;
    for (int i = 1; i < length + 1; i++)
    {
        if ((min > a[i].num)&&(b[i] == 0))
        {
            min = a[i].num;
            start = i;
        }
    }
    return min;
}
void Dijkstra(int& total, int** Arcs, int N, int start)
{
    int* a = new int[N + 1];
    Array* b = new Array[N + 1];
    memset(a, 0, sizeof(int) * (N + 1));
    for (int i = 0; i < N + 1; i++)
    {
        b[i].num = 10000;
    }
    a[start] = 1;
    int startcopy = start;
    int min = 0;
    for (int j = 0; j < N; j++)
    {
        for (int i = 1; i < N + 1; i++)
        {
            if ((Arcs[start][i] > 0) && (a[i] == 0))
            {
                if (b[i].num > min + Arcs[start][i])
                {
                    b[i].num = Arcs[start][i] + min;
                }
            }
        }
        min = Min(b, N, start, a);
        a[start] = 1;
    }
    b[startcopy].num = 0;
    for (int i = 1; i < N + 1; i++)
    {
        total += b[i].num;
    }


}
int main()
{
    int N;
    int M;
    cin >> N;
    cin.ignore();
    cin >> M;
    cin.ignore();
    int** Arcs = new int* [N + 1];
    for (int i = 0; i < N + 1; i++)
    {
        Arcs[i] = new int[N + 1];
    }
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            Arcs[i][j] = 0;
        }
    }
    int start;
    int end;
    for (int i = 0; i < M; i++)
    {
        cin >> start;
        cin.ignore();
        cin >> end;
        cin.ignore();
        Arcs[start][end] = 1;
        Arcs[end][start] = 1;
    }
    int t;
    cin >> t;
    cin.ignore();
    int* inquirement = new int[t];
    memset(inquirement, 0, sizeof(int) * (t));
    int* total = new int[t];
    memset(total, 0, sizeof(int) * (t));
    for (int i = 0; i < t; i++)
    {
        cin >> inquirement[i];
        cin.ignore();
        Dijkstra(total[i], Arcs, N, inquirement[i]);
    }
    for (int i = 0; i < t;i++)
    {
        cout << "Cc(" << inquirement[i] << ") = " <<setiosflags(ios::fixed)<<setprecision(2)<< (double(N - 1) / double(total[i]))  << endl;
    }

   
}