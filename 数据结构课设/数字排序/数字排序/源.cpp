/*
9����1���������򣨹�ϣ������
[��������]
��������n����������ͳ�Ƴ�ÿ���������ֵĴ����������ִ����Ӷൽ�ٵ�˳�������
�����ʽ
��������ĵ�һ�а���һ������n����ʾ�������ֵĸ�����
�����ڶ��а���n�����������ڵ�����֮����һ���ո�ָ�����ʾ��������������
�����ʽ
������У�ÿ�а��������������ֱ��ʾһ�������������������ֵĴ����������ִ����ݼ���˳�������
��������������ֵĴ���һ���࣬�������ֵ��С�ģ�Ȼ�����ֵ�ϴ�ġ�
��������
13
5 2 3 3 1 3 4 2 5 2 3 5 0
�������
3 4
2 3
5 3
1 1
4 1
�������������Ŀ����һ�����飬���±���Ϊ�����������ݴ洢�������ִ�����ʵ�֣�����൱��ֱ��ӳ�䣬
�ǻ�����Ŀ���泣�õ�һ�ֽ��ⷨ���ܶ࿴�Ʒ����Ե����������ʵ�����Բ�ȡ��ϣ����ӳ��ķ������ɽ⣬
����ϣ˼���ڻ�����Ŀ�е�����
*/

#include <iostream>
using namespace std;

typedef struct {
	int serial;
	int num;
}Array;
void Swap(Array& a, Array& b)
{
	int temp;
	temp = a.num;
	a.num = b.num;
	b.num = temp;
	temp = a.serial;
	a.serial = b.serial;
	b.serial = temp;
}
int main()
{
	Array Array[1001];
	for (int i = 0; i < 1001; i++)
	{
		Array[i].num = 0;
		Array[i].serial = i;
	}

	int n;
	int max = 0;
	int a;
	int count = 0;
	cin >> n;
	cin.ignore();
	for (int i = 0; i < n; i++)
	{
		cin >> a;
		cin.ignore();
		if (a > max)
		{
			max = a;
		}
		Array[a].num++;
	}
	int maxnum = 0;
	int maxserial = 0;
	for (int i = 0; i < n; i++)
	{
		if (Array[i].num != 0)
		{
			count++;
		}
	}
	for (int i = 0; i < 1001; i++)
	{
		for (int j = 0; j < 1000 - i; j++)
		{
			if (Array[j].num < Array[j + 1].num)
			{
				Swap(Array[j], Array[j + 1]);
			}
		}
	}
	for (int i = 0; i < 1001; i++)
	{
		if (Array[i].num != 0)
		{
			cout << Array[i].serial << " " << Array[i].num << endl;
		}
		
	}
	return 0;
	
}