/*
9、【1】数字排序（哈希、排序）
[问题描述]
　　给定n个整数，请统计出每个整数出现的次数，按出现次数从多到少的顺序输出。
输入格式
　　输入的第一行包含一个整数n，表示给定数字的个数。
　　第二行包含n个整数，相邻的整数之间用一个空格分隔，表示所给定的整数。
输出格式
输出多行，每行包含两个整数，分别表示一个给定的整数和它出现的次数。按出现次数递减的顺序输出。
如果两个整数出现的次数一样多，则先输出值较小的，然后输出值较大的。
样例输入
13
5 2 3 3 1 3 4 2 5 2 3 5 0
样例输出
3 4
2 3
5 3
1 1
4 1
问题分析：该题目可用一个数组，以下标作为数，数组内容存储该数出现次数来实现（这就相当于直接映射，
是机试题目里面常用的一种解题法，很多看似非线性的题型最后其实都可以采取哈希或者映射的方法来巧解，
体会哈希思想在机试题目中的巧用
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