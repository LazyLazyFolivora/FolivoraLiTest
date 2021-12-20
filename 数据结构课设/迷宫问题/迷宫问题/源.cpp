/*2、迷宫问题（必做）（栈与队列）
[问题描述]
利用栈操作实现迷宫问题求解。
[基本要求]
（1）从文件中读取数据，生成模拟迷宫地图，不少于20行20列。
（2）给出任意入口和出口，显示输出迷宫路线。*/


//默认0为墙，1为路径,2为路线，-1为已走过不可行的路
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
typedef struct {
	int X;
	int Y;
}Position;
#define SElemType Position
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
using namespace std;
typedef struct {
	SElemType* top;
	SElemType* base;
	int stacksize;
}SqStack;

void InitStack(SqStack& S)
{
	S.base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!S.base)
	{
		cout << "内存分配失败！" << endl;
		exit(1);
	}
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
}
void PushStack(SqStack& S, SElemType e)
{
	if (S.top - S.base >= S.stacksize)
	{
		S.base = (SElemType*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));
		if (!S.base)
		{
			cout << "内存分配失败！" << endl;
			exit(1);
		}
		S.top = S.base + S.stacksize;
		S.stacksize = S.stacksize + STACKINCREMENT;
	}
	*(S.top) = e;
	S.top++;

}
void PopStack(SqStack& S, SElemType& e)
{
	S.top--;
	e = *(--(S.top));
	S.top++;
}

bool EmptyStack(SqStack S)
{
	if (S.top <= S.base)
	{
		return true;
	}
	return false;
}

void Print(int** map, int row, int line)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < line; j++)
		{
			cout <<setiosflags(ios::right)<<setw(4)<< map[i][j];
		}
		cout << endl;
	}
	cout << endl;
	cout << endl;
}
int main()
{
	int row;
	int line;
	fstream file1;
	file1.open("D:\\maze.txt", ios::in);
	if (file1.fail())
	{
		cout << "error" << endl;
		exit(1);
	}
	file1 >> row;
	file1 >> line;
	int** map = new int* [row];
	for (int i = 0; i < row; i++)
	{
		map[i] = new int[line];
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < line; j++)
		{
			file1 >> map[i][j];
		}
	}
	int startX;
	int startY;
	int endX;
	int endY;
	cin >> startY;
	cin.ignore();
	cin >> startX;
	cin.ignore();
	cin >> endY;
	cin.ignore();
	cin >> endX;
	cin.ignore();
	SqStack s;
	InitStack(s);
	Position current;
	current.X = startX;
	current.Y = startY;
	map[startX][startY] = 3;
	map[endX][endY] = 4;
	bool IsHavePath = true;			//默认有路
	
	int word = 0;

	while ((current.X != endX) || (current.Y != endY))
	{
		if (map[startX][startY] == -1)
		{
			IsHavePath = false;
			break;
		}
		//cout << current.X << endl;
		if (current.Y < line - 1)
		{
			if (map[current.X][current.Y + 1] == 4)
			{
				break;
			}
			if (map[current.X][current.Y + 1] == 1)   //向右走
			{
				if ((current.X != startX) || (current.Y + 1 != startY))
				{
					map[current.X][current.Y + 1] = 2;
				}
				//Print(map, row, line);
				current.Y++;
				PushStack(s, current);
				continue;
			}
			
		}
		if (current.X > 0)
		{
			if (map[current.X - 1][current.Y] == 4)
			{
				break;
			}
			if (map[current.X - 1][current.Y] == 1)	//向上走
			{
				
				if ((current.X - 1 != startX) || (current.Y != startY))
				{
					map[current.X - 1][current.Y] = 2;
				}
				//Print(map, row, line);
				current.X--;
				PushStack(s, current);
				continue;
			}

		}
		if (current.Y > 0)
		{
			if (map[current.X][current.Y - 1] == 4)
			{
				break;
			}
			if (map[current.X][current.Y - 1] == 1)	//向左走
			{
				
				if ((current.X != startX) || (current.Y - 1 != startY))
				{
					map[current.X][current.Y - 1] = 2;
				}
				//Print(map, row, line);
				current.Y--;
				PushStack(s, current);
				continue;
			}
		}
		if (current.X < row - 1)
		{
			if (map[current.X + 1][current.Y] == 4)
			{
				break;
			}
			if (map[current.X + 1][current.Y] == 1)	//向下走
			{
				
				if ((current.X + 1!= startX) || (current.Y != startY))
				{
					map[current.X + 1][current.Y] = 2;
				}
				//Print(map, row, line);
				current.X++;
				PushStack(s, current);
				continue;
			}
		}
		map[current.X][current.Y] = -1;
		//Print(map, row, line);
		PopStack(s, current);
		if (EmptyStack(s))
		{
			current.X = startX;
			current.Y = startY;
			if (word == 0)
			{
				if (current.X > 0)
				{
					if (map[current.X - 1][current.Y] == 1)	//向上走
					{
						current.X--;
						PushStack(s, current);
						current.X++;
					}

				}
				word++;
				continue;
			}
			else if (word == 1)
			{
				if (current.Y > 0)
				{
					if (map[current.X][current.Y - 1] == 1)	//向左走
					{
						current.Y--;
						PushStack(s, current);
						current.Y++;
					}
				}
				word++;
				continue;
			}
			
			else if (word == 2)
			{
				if (current.X < row - 1)
				{
					if (map[current.X + 1][current.Y] == 1)
					{
						current.X++;
						PushStack(s, current);
						current.X--;
					}
				}
			}
			else if (word == 3)
			{
				IsHavePath = false;
				break;
			}
		}
	}
	if (IsHavePath == false)
	{
		cout << "此时迷宫不存在路径" << endl;
		return 0;
	}
	else
	{
		cout << "存在路径如下:" << endl;
		Print(map, row, line);
		
	}


}