// @author: Folivora Li
// @copyright: Folivora Li


/*16����2���г�·��  (ѡ��)��ͼ��
[��������]
����С����С����ȥ����棬С�����𿪳���С����������
����С�������ܵĵ�·��Ϊ�����С��������ȽϺ��ߣ�ÿ��1����С��������1��ƣ�Ͷȡ�С�������ߣ�
  ���������С����С����ƣ��ֵ��������ӣ�������s����С��������s2��ƣ�Ͷȡ�
�������磺��5��·�ڣ�1��·�ڵ�2��·��ΪС����2��·�ڵ�3��·��ΪС����3��·�ڵ�4��·��Ϊ���
  ��4��·�ڵ�5��·��ΪС��������·��֮��ľ��붼��2������С����1��·�ڵ�5��·�ڣ�
  ����ƣ��ֵΪ(2+2)2+2+22=16+2+4=22��
����С���õ��˵�ͼ����������滮һ��������·�ߣ�ʹ�ð����·�߿���С����ƣ�Ͷ���С��
[����Ҫ��]
�����ʽ��
��������ĵ�һ�а�����������n, m���ֱ��ʾ·�ڵ������͵�·��������·����1��n��ţ�
  С����Ҫ������1��·�ڵ�n��·�ڡ�
������m��������·��ÿ�а����ĸ�����t, a, b, c����ʾһ������Ϊt������a��b����·�ڣ�
����Ϊc�����˫���·������tΪ0��ʾ�����tΪ1��ʾС������֤1��·�ں�n��·������ͨ�ġ�
�����ʽ
���һ����������ʾ����·����С����ƣ�Ͷȡ�
��������
6 7
1 1 2 3
1 2 3 2
0 1 3 30
0 3 4 20
0 4 5 30
1 3 5 6
1 5 6 1
�������
76
����˵��
������1��С����2������С����3��ƣ�Ͷ�Ϊ52=25��Ȼ���3�ߴ������4����5��ƣ�Ͷ�Ϊ20+30=50��
  ����5��С����6��ƣ�Ͷ�Ϊ1���ܹ�Ϊ76��
�γ����Ҫ��
��1��Ҫ����ı��ļ������룻
��2�������ʵ������ݽṹ�洢�����������еĵ�·���γɵ�ͼ�ṹ��
��3����д�������ŵ��㷨�������������С����ɵ�ƣ��ֵ��ָ������
����ʾ�����ڵϽ�˹�����㷨���иĽ�������ɱ��⣩��
��4�����ϸ���ĿҪ�����������⣬��Ҫ���������·�ߵ�·����
�Լ��ӳ����㵽���������Сƣ��ֵ��*/

//��������������󣬸��˾������ⲻ����dijkstra���ģ���Ϊ����ıߵ�Ȩֵ���ǹ̶��ģ���ǰһ������
//�ı��й�ϵ�����ض�������൱�ڲ����˸�Ȩ�ߣ�������֪��dijkstraֻ����û�и�Ȩ�ߵ���С·��
//��Ȼ���Ǹ���Ҫ����dijkstraд�ˣ���ʵ�ǲ������- -
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

//0�Ǵ��,1��С��

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
    int* a = new int[n + 1];        //���Ƿ񱻷��ʹ�
    int* b = new int[n + 1];        //�����·��ֵ
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
    cout << "���·��Ϊ:";
    for (int i = 0; i < con.size() - 1; i++)
    {
        cout << con[i] << "-->";
    }
    cout << con[con.size() - 1] << endl;
    cout << "��̾���Ϊ" << b[n] << endl;
    cout << "����㵽���������̾���Ϊ:";
    for (int i = 2; i < n + 1; i++)
    {
        cout << "����" << i << ":" << b[i] << endl;
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