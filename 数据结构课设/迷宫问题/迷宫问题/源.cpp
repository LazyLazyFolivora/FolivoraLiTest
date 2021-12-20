/*2���Թ����⣨��������ջ����У�
[��������]
����ջ����ʵ���Թ�������⡣
[����Ҫ��]
��1�����ļ��ж�ȡ���ݣ�����ģ���Թ���ͼ��������20��20�С�
��2������������ںͳ��ڣ���ʾ����Թ�·�ߡ�*/


//Ĭ��0Ϊǽ��1Ϊ·��,2Ϊ·�ߣ�-1Ϊ���߹������е�·
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
		cout << "�ڴ����ʧ�ܣ�" << endl;
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
			cout << "�ڴ����ʧ�ܣ�" << endl;
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
	bool IsHavePath = true;			//Ĭ����·
	
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
			if (map[current.X][current.Y + 1] == 1)   //������
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
			if (map[current.X - 1][current.Y] == 1)	//������
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
			if (map[current.X][current.Y - 1] == 1)	//������
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
			if (map[current.X + 1][current.Y] == 1)	//������
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
					if (map[current.X - 1][current.Y] == 1)	//������
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
					if (map[current.X][current.Y - 1] == 1)	//������
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
		cout << "��ʱ�Թ�������·��" << endl;
		return 0;
	}
	else
	{
		cout << "����·������:" << endl;
		Print(map, row, line);
		
	}


}