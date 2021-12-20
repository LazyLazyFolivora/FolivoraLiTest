#include <iostream>
#include <ctime>
#include <Windows.h>
#include <fstream>
using namespace std;
int main()
{
	int a[50000];
	int temp1;
	fstream file;
	fstream file1;
	file.open("D:\\rand8.txt", ios::out);
	file1.open("D:\\rand9.txt", ios::out);
	if (file.fail())
	{
		cout << "error!" << endl;
	}
	if (file1.fail())
	{
		cout << "error1!" << endl;
	}
	int b;
	for (int i = 0; i < 50000; i++)
	{
		srand((unsigned)time(NULL) * i);
		b = i;
		if (b > 773)
		{
			b = b % 773;
		}
		temp1 = rand() * b * 7;
		if (temp1 > 5000000)
		{
			temp1 = temp1 % 5000000;
		}
		a[i] = temp1;
		Sleep(1);
		

	}
	int Sedgewick[12] = { 1,5,19,41,109,209,505,929,2161,3905,8929,16001 };
	int length = 12;
	for (int i = length - 1; i >= 0; i--)
	{
		if (Sedgewick[i] > 50000)
		{
			length--;
		}
		else
		{
			break;
		}
	}
	int deita;
	int temp;
	int k;
	for (int i = length - 1; i >= 0; i--)
	{
		deita = Sedgewick[i];
		for (int j = deita; j < 50000; j = j + deita)
		{
			temp = a[j];
			for (k = j - deita; k >= 0; k = k - deita)
			{
				if (temp < a[k])
				{
					a[k + deita] = a[k];
				}
				else
				{
					break;
				}
			}
			a[k + deita] = temp;
		}

	}
	for (int i = 0; i < 50000; i++)
	{
		cout << a[i] << " ";
		file << a[i];
		file << " ";
		file1 << a[49999 - i];
		file1 << " ";
	}
	file.close();
	file1.close();
	
}