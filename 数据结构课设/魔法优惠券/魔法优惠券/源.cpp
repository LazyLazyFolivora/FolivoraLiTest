// @author: Folivora Li
// @copyright: Folivora Li

/*11����1�� ħ���Ż�ȯ��ѡ����������
[��������]
�ڻ������и�ħ���̵꣬ͨ��ħ���Ż�ȯ��ÿ���Ż�ȯ��ӡ��һ��������ֵK��
��ʾ�����ڹ���ĳ��Ʒʹ�������Ż�ȯ�����Եõ�K������Ʒ��ֵ�Ļر���
���̵껹�������һЩ�м�ֵ����Ʒ�������������ȡ�����Ʒ��ʱ��ʹ����ֵΪ�����Ż�ȯ��
����뵹������ƷK������Ʒ��ֵ�Ľ������ǲ�Ҫ����������ֵΪ�����Ż�ȯ�����á�
���磬����һ���Ż�ȯ����ֵ�ֱ�Ϊ1��2��4��-1����Ӧһ����Ʒ����ֵΪ���Ǳ�7��6��-2��-3��
���и��ļ�ֵ��ʾ����Ʒ�������Ʒ�����ǿ��Խ��Ż�ȯ3����ֵ4��������Ʒ1����ֵ7���ϣ�
�õ����Ǳ�28�Ļر����Ż�ȯ4����ֵ-1��������Ʒ4����ֵ-3���ϣ��õ����Ǳ�3�Ļر���
���ǣ����һ��С�İ��Ż�ȯ3����ֵ4���õ���Ʒ4����ֵ-3���ϣ�����뵹�����̵���Ǳ�12����
ͬ�������Ż�ȯ4����ֵ-1���õ���Ʒ1����ֵ7���ϣ�����뵹�����̵���Ǳ�7����
�涨ÿ���Ż�ȯ��ÿ����Ʒ��ֻ����౻ʹ��һ�Σ�������Եõ������ر��� 
[����Ҫ��]
��1������˵�������������С���һ�����ȸ����Ż�ȯ�ĸ���N��������N���Ż�ȯ��������ֵ�� 
�ڶ������ȸ�����Ʒ�ĸ���M��������M����Ʒ��������ֵ��N��M��[1,106]֮�䣬���е����ݴ�С������230
�����ּ��Կո�ָ��� 
��2�����˵����������Եõ������ر���
��3������������ 
4 1 2 4 -1
      4 7 6 -2 -3
  43

���룺4 3 2 6 1 
      3 2 6 3
�����49

���룺 7 3 36 -1 73 2 3 6
       6 -1 -1 -1 -1 -1 -1
����� 1*/


#include <iostream>
#include <algorithm>
using namespace std;
int Min(int a, int b)
{
    if (a > b)
    {
        return b;

    }
    else
    {
        return a;
    }
}
int main()
{
    int N;
    cin >> N;
    cin.ignore();
    int* a = new int[N];
    int positive1 = 0;
    int positive2 = 0;
    int negative1 = 0;
    int negative2 = 0;
    for (int i = 0; i < N; i++)
    {
        cin >> a[i];
        cin.ignore();
        if (a[i] > 0)
        {
            positive1++;
        }
    }
    negative1 = N - positive1;
    int M;
    cin >> M;
    cin.ignore();
    int* b = new int[M];
    for (int i = 0; i < M; i++)
    {
        cin >> b[i];
        cin.ignore();
        if (b[i] > 0)
        {
            positive2++;
        }

    }
    negative2 = N - positive2;
    sort(a, a + N, greater<int>());
    sort(b, b + M, greater<int>());
    int min = Min(positive1, positive2);
    int total = 0;
    for (int i = 0; i < min; i++)
    {
        total = total + a[i] * b[i];
    }
    min = Min(negative1, negative2);
    reverse(a, a + N);
    reverse(b, b + M);
    for (int i = 0; i < min; i++)
    {
        total = total + a[i] * b[i];
    }
    cout << total << endl;
}