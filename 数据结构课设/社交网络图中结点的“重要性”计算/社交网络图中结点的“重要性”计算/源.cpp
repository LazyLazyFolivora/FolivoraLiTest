// @author: Folivora Li
// @copyright: Folivora Li

/*10����1�� �罻����ͼ�н��ġ���Ҫ�ԡ����㣨ѡ������ͼ��
[��������]
���罻�����У����˻�λ����㣩֮��ͨ��ĳЩ��ϵ���ߣ���ϵ�����������ܵ���Щ��ϵ��Ӱ�죬
����Ӱ��������Ϊ�������໥���ӵĽ��֮�����ӵ�һ���໥���ã�������ǿҲ���Լ�����
����������������λ�ò�ͬ�������������ֵ���Ҫ��Ҳ������ͬ��
�����ܶ������ԡ�����������һ�����ﵽ�������ġ���������ָ�꣬��һ���нϸ������ԵĽ���
�нϵ������ԵĽ���ܹ�����أ�ƽ�������£����������е�������㣬����ڸ�����Ĵ�����������
����Ҫ�ļ�ֵ������N�����������У����vi�ġ����ܶ������ԡ� ��ѧ�϶���Ϊ ���������н��(j!=i)
����̾����ƽ��ֵ�ĵ�����

���ڷ���ͨͼ�����н��Ľ��ܶ������Զ���0��
��ʵ�����һ����Ȩ������ͼ�Լ����е�һ���㣬Ҫ�������������ÿ�����Ľ��ܶ������ԡ�

[����Ҫ��]
��1������˵��������ĵ�һ�и�������������N (N<=1000)��M������N��ͼ�н�����������Ŵ�1��N��
M��M<=10000���Ǳߵ���Ŀ������M���У�ÿ�и���һ���ߵ���Ϣ�����ñ����ӵ���������ţ�
�м��ÿո�ָ������һ�и�����Ҫ������ܶ������Ե�������ĸ���K��K<=100�����Լ�K�����ı�ţ�
�ÿո�ָ���
��2�����˵�������ա�Cc(i)=x.xx���ĸ�ʽ���K���������Ľ��ܶ������ԣ�ÿ�����ռһ�У�
�����ȷ��С�����2λ�� 
��3������������ 
����  5 8
      1 2
      1 3
      1 4
      2 3
      3 4
      4 5
      2 5
      3 5
      2 4 3
���  Cc(4) = 0.80
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