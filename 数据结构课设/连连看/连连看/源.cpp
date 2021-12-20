/*18、【2】编写“连连看”程序。(选做)（图）
[问题描述]
建立一个10*20的矩形方格图，其中有10种不同的图案，每种图案个数为偶数，填满矩形方格图。
[基本要求]
（1）随机产生原始数据
（2）输入两个位置，如果两者图案相同，并且用少于等于3的直线相连，可消除该两个图案。*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <stdlib.h>
#include <iomanip>
using namespace std;
void GeneratePattern(int map[12][22])
{
	vector<int> a;
	vector<int>::iterator iter;
	for (int i = 0; i < 200; i++)
	{
		a.push_back(i);
	}
	int a1;
	int b1;
	int pattern;
	srand(time(NULL));
	iter = a.begin();
	while (a.size() > 0)
	{
		pattern = rand() % 10;
		a1 = rand() % a.size();
		map[a[a1] % 10 + 1][a[a1] / 10 + 1] = pattern;
		a.erase(iter + a1);
		iter = a.begin();
		b1 = rand() % a.size();
		map[a[b1] % 10 + 1][a[b1] / 10 + 1] = pattern;
		a.erase(iter + b1);
		srand(time(NULL) * b1);
		iter = a.begin();
	}
}

int Min(int a, int b)
{
	if (a < b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

int Max(int a, int b)
{
	if (a < b)
	{
		return b;
	}
	else
	{
		return a;
	}
}

//两色块行相等
bool Rowequal(int map[12][22], int y1, int y2, int x)
{
	int word = 0;
	if (y2 - y1 == 1)
	{
		return true;
	}
	for (int i = y1 + 1; i < y2; i++)
	{
		if (map[x][i] >= 0)
		{
			word = 1;
		}
	}
	if (word == 0)
	{
		return true;
	}
	//向上找
	for (int i = x - 1; i >= 0; i--)
	{
		int word1 = 0;
		if (map[i][y1] == -1)
		{
			for (int j = y1; j <= y2; j++)
			{
				if (map[i][j] != -1)
				{
					word1 = 1;
					break;
				}
			}
			if (word1 == 0)
			{
				for (int j = i; j < x; j++)
				{
					if (map[j][y2] != -1)
					{
						word1 = 1;
						break;
					}
				}
				if (word1 == 0)
				{
					return true;
				}
			}
		}
		else
		{
			break;
		}
	}
	//向下找
	for (int i = x + 1; i <= 11; i++)
	{
		int word1 = 0;
		if (map[i][y1] == -1)
		{
			for (int j = y1; j <= y2; j++)
			{
				if (map[i][j] != -1)
				{
					word1 = 1;
					break;
				}
			}
			if (word1 == 0)
			{
				for (int j = i; j > x; j--)
				{
					if (map[j][y2] != -1)
					{
						word1 = 1;
						break;
					}
				}
				if (word1 == 0)
				{
					return true;
				}
			}
		}
		else
		{
			break;
		}
	}
	return false;
}
//两色块列相等
bool Lineequal(int map[12][22], int x1, int x2, int y)
{
	int word = 0;
	if (x2 - x1 == 1)
	{
		return true;
	}
	for (int i = x1 + 1; i < x2; i++)
	{
		if (map[i][y] >= 0)
		{
			word = 1;
		}
	}
	if (word == 0)
	{
		return true;
	}
	//向左找
	for (int i = y - 1; i >= 0; i--)
	{
		int word1 = 0;
		if (map[x1][i] == -1)
		{
			for (int j = x1; j <= x2; j++)
			{
				if (map[j][i] != -1)
				{
					word1 = 1;
					break;
				}
			}
			if (word1 == 0)
			{
				for (int j = i; j < y; j++)
				{
					if (map[x2][j] != -1)
					{
						word1 = 1;
						break;
					}
				}
				if (word1 == 0)
				{
					return true;
				}
			}
		}
		else
		{
			break;
		}
	}
	//向下找
	for (int i = y + 1; i <= 21; i++)
	{
		int word1 = 0;
		if (map[x1][i] == -1)
		{
			for (int j = x1; j <= x2; j++)
			{
				if (map[j][i] != -1)
				{
					word1 = 1;
					break;
				}
			}
			if (word1 == 0)
			{
				for (int j = i; j > y; j--)
				{
					if (map[x2][j] != -1)
					{
						word1 = 1;
						break;
					}
				}
				if (word1 == 0)
				{
					return true;
				}
			}
		}
		else
		{
			break;
		}
	}
	return false;
}

bool Diagonal_pos(int map[12][22], int x1, int y1, int x2, int y2)
{
	//向上找
	for (int i = x1; i >= 0; i--)
	{
		int word = 0;
		if (i != x1)
		{
			if (map[i][y1] != -1)
			{
				break;
			}
		}
		for (int j = y1 + 1; j <= y2; j++)
		{
			if (map[i][j] >= 0)
			{
				word = 1;
				break;
			}
		}
		if (word == 0)
		{
			for (int j = i; j < x2; j++)
			{
				if (map[j][y2] >= 0)
				{
					word = 1;
					break;
				}
			}
			if (word == 0)
			{
				return true;
			}
		}
	}
	//向下找
	for (int i = x1 + 1; i <= 11; i++)
	{
		int word = 0;
		if (map[i][y1] != -1)
		{
			break;
		}
		for (int j = y1 + 1; j <= y2; j++)
		{
			if (map[i][j] >= 0)
			{
				word = 1;
				break;
			}
		}
		if (word == 0)
		{
			for (int j = i; j > x2; j--)
			{
				if (map[j][y2] >= 0)
				{
					word = 1;
					break;
				}

			}
			if (word == 0)
			{
				return true;
			}
		}
	}
	//向左找
	for (int i = y1; i >= 0; i--)
	{
		int word = 0;
		if (i != y1)
		{
			if (map[x1][i] != -1)
			{
				break;
			}
		}
		for (int j = x1 + 1; j <= x2; j++)
		{
			if (map[j][i] >= 0)
			{
				word = 1;
				break;
			}
		}
		if (word == 0)
		{
			for (int j = i; j < y2; j++)
			{
				if (map[x2][j] >= 0)
				{
					word = 1;
					break;
				}

			}
			if (word == 0)
			{
				return true;
			}
		}
	}
	//向右找
	for (int i = y1 + 1; i <= 21; i++)
	{
		int word = 0;
		if (map[x1][i] != -1)
		{
			break;
		}
		for (int j = x1 + 1; j <= x2; j++)
		{
			if (map[j][i] >= 0)
			{
				word = 1;
				break;
			}
		}
		if (word == 0)
		{
			for (int j = i; j > y2; j--)
			{
				if (map[x2][j] >= 0)
				{
					word = 1;
					break;
				}

			}
			if (word == 0)
			{
				return true;
			}
		}
	}
	return false;
}
//反对角线

bool IsErase(int map[12][22], int x1, int y1, int x2, int y2)
{
	if (x1 == x2)
	{
		if (Rowequal(map, Min(y1, y2), Max(y1, y2), x1))
		{
			map[x1][y1] = -1;
			map[x2][y2] = -1;
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (y1 == y2)
	{
		if (Lineequal(map, Min(x1, x2), Max(x1, x2), y1))
		{
			map[x1][y1] = -1;
			map[x2][y2] = -1;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (((x2 - x1) * (y2 - y1)) > 0)
		{
			if (Diagonal_pos(map, Min(x1, x2), Min(y1, y2), Max(x1, x2), Max(y1, y2)))
			{
				map[x1][y1] = -1;
				map[x2][y2] = -1;
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			if (Diagonal_pos(map, Max(x1, x2), Min(y1, y2), Min(x1, x2), Max(y1, y2)))
			{
				map[x1][y1] = -1;
				map[x2][y2] = -1;
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}
void Print(int map[12][22])
{
	for (int i = 1; i <= 10; i++)
	{
		for (int j = 1; j <= 20; j++)
		{
			cout << setw(4) << std::left << map[i][j];
		}
		cout << endl;
	}
}
bool IsFinish(int map[12][22])
{
	for (int i = 1; i <= 10; i++)
	{
		for (int j = 1; j <= 20; j++)
		{
			if (map[i][j] != -1)
			{
				return false;
			}
		}
	}
	return true;
}
int main()
{
	int map[12][22];
	memset(map, -1, sizeof(int) * 264);
	//初始图案用0到9代替
	GeneratePattern(map);
	Print(map);
	int x1;
	int y1;
	int x2;
	int y2;
	while (1)
	{
		cout << "请输入第一个色块的行和列" << endl;
		cin >> x1;
		cin.ignore();
		cin >> y1;
		cin.ignore();
		cout << "请输入第二个色块的行和列" << endl;
		cin >> x2;
		cin.ignore();
		cin >> y2;
		cin.ignore();
		if (x1 == x2 && y1 == y2)
		{
			cout << "请不要输入同样的坐标！" << endl;
			continue;
		}
		if (map[x1][y1] != map[x2][y2])
		{
			cout << "两色块颜色不同，无法消除！" << endl;
			continue;

		}
		if (!IsErase(map, x1, y1, x2, y2))
		{
			cout << "这两个色块无法消除" << endl;
		}
		Print(map);
		if (IsFinish(map))
		{
			cout << "恭喜你，全部色块清除，游戏结束！" << endl;
			break;
		}
	}

}