#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
struct Roads;
struct Station;
using namespace std;
struct Roads {
	struct Station* next;//下一站车站
	int Busnumber;//路线号
};

struct Station {
	string name;//车站名
	struct Roads* road[200];//到下一站的路线
	int roadnum = 0;
};



typedef struct {
	struct Station station[10000];
	int stationnum = 0;
}Map;

void ReadFile(Map*& Map)
{
	fstream file;
	file.open("D:\\南京公交线路.txt", ios::in);
	if (file.fail())
	{
		cout << "error!" << endl;
		exit(1);
	}
	int busnumber;
	char a = 'p';
	int i = 0;
	map<string, int>stations;
	map<string, int>::iterator iter;
	string tempname = "";
	string lastname = " ";
	string tempbuf = " ";
	string lastbuf = "";
	string buf1;
	int j1 = 0;
	int word = 0;
	int start = 0;
	while (1)
	{
		
		if (start == 0)
		{
			file >> busnumber;
			cout << endl;
			cout << busnumber << ":" << endl;
			file.seekg(5, ios::cur);
			//file >> a;
			lastname = " ";
			getline(file, buf1);
		}
		
		cout << buf1;
		while (j1 < buf1.length())
		{
			while ((buf1[j1] != ',') && (j1 < buf1.length()))
			{
				tempname += buf1[j1++];
			}
			j1++;
			if (Map->station[i].roadnum == 0)
			{

				for (int i1 = 0; i1 < 200; i1++)
				{
					Map->station[i].road[i1] = new Roads;
					Map->station[i].road[i1]->next = new Station;
				}

			}

			cout << tempname << endl;
			if (lastname != " ")
			{
				Map->station[i - 1].road[Map->station[i - 1].roadnum]->Busnumber = busnumber;
				Map->station[i - 1].road[Map->station[i - 1].roadnum++]->next = &(Map->station[i]);
				Map->station[i].road[Map->station[i].roadnum]->Busnumber = busnumber;
				Map->station[i].road[Map->station[i].roadnum++]->next = &(Map->station[i - 1]);
			}
			if (stations.find(tempname) == stations.end())  //之前没有读取过这个站点
			{

				stations.insert(pair<string, int>(tempname, i));
				Map->station[i].name = tempname;
				i++;
				Map->stationnum++;
			}
			lastname = tempname;
			tempname = "";
			
		}
		file >> busnumber;
		cout << endl;
		cout << busnumber << ":" << endl;
		file.seekg(5, ios::cur);
		lastname = " ";
		if (!getline(file, buf1))
		{
			break;
		}
		j1 = 0;
		start = 1;
	}
	for (iter = stations.begin(); iter != stations.end() ; iter++)
	{
		cout << iter->first << "  " << iter->second << endl;
	}
	cout << Map->stationnum;
}
int main()
{
	Map* M = new Map;
	ReadFile(M);
}