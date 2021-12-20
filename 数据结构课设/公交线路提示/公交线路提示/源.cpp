// @author: Folivora Li
// @copyright Folivora Li


/*
6、公交线路提示  (必做) （图）
[问题描述]
上网下载真实南京公交线路图，建立南京主要公交线路图的存储结构。
[基本要求]
（1）输入任意两站点，给出转车次数最少的乘车路线。
（2）输入任意两站点，给出经过站点最少的乘车路线。
*/
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
	bool IsSigned = false;
	bool StackSigned = false;
	Station* laststation = NULL;
};

typedef struct {
	struct Station station[10000];
	int stationnum = 0;
}Map;

typedef struct QueueNode{
	Station station;
	QueueNode* next;

}QueueNode;

typedef struct {
	QueueNode* front;
	QueueNode* rear;
}LinkQueue;


void InitQueue(LinkQueue& Q)
{
	Q.front = Q.rear = new QueueNode;
	if (!Q.front)
	{
		exit(1);
	}
	Q.front->next = NULL;
}
void EnQueue(LinkQueue& Q, Station e)
{
	QueueNode* q = new QueueNode;
	q->station = e;
	q->next = NULL;
	Q.rear->next = q;
	Q.rear = q;


}
void ClearQueue(LinkQueue& Q)
{
	Q.rear = Q.front;
}

void DestroyQueue(LinkQueue& Q)
{
	while (Q.front)
	{
		Q.rear = Q.front->next;
		delete(Q.front);
		Q.front = Q.rear;
	}
}

bool QueueEmpty(LinkQueue Q)
{
	if (Q.front == Q.rear)
	{
		return true;
	}
	return false;
}

void DeQueue(LinkQueue& Q,Station& e)
{
	if (Q.front == Q.rear)
	{
		return;
	}
	QueueNode* q;
	q = Q.front->next;
	Q.front->next = q->next;
	if (q->next != NULL)
	{
		e = q->next->station;
	}
	else
	{
		Q.rear = Q.front;
		return;
	}
	
	if (q == Q.rear)
	{
		Q.rear = Q.front;
	}
	delete q;
}



void ReadFile(Map*& Map, map<string, int>& stations)
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
	map<string, int>::iterator iter;
	string tempname = "";
	string lastname = " ";
	string tempbuf = " ";
	string lastbuf = "";
	string buf1;
	int j1 = 0;
	int word = 0;
	int start = 0;
	int lastserial = 0;
	int thisserial = 0;
	while (1)
	{

		if (start == 0)
		{
			file >> busnumber;
			//cout << endl;
			//cout << busnumber << ":" << endl;
			file.seekg(5, ios::cur);
			//file >> a;
			lastname = " ";
			getline(file, buf1);
		}

		//cout << buf1;
		while (j1 < buf1.length())
		{
			while ((buf1[j1] != ',') && (j1 < buf1.length()))
			{
				tempname += buf1[j1++];
			}
			j1++;
			if (Map->station[i].roadnum == 0)
			{
				for (int i1 = 0; i1 < 150; i1++)
				{
					Map->station[i].road[i1] = new Roads;
					Map->station[i].road[i1]->next = new Station;
				}
			}

			//cout << tempname << endl;
			if (stations.find(tempname) == stations.end())  //之前没有读取过这个站点
			{
				
				if (i == 0)
				{
					i++;
				}
				else if (i != 0)
				{
					lastserial = thisserial;
					thisserial = i;
					i++;
				}
				stations.insert(pair<string, int>(tempname, thisserial));
				Map->station[thisserial].name = tempname;
				Map->stationnum++;
			}
			else
			{
				iter = stations.find(tempname);
				lastserial = thisserial;
				thisserial = iter->second;
			}
			if (lastname != " ")
			{
				Map->station[lastserial].road[Map->station[lastserial].roadnum]->Busnumber = busnumber;
				Map->station[lastserial].road[Map->station[lastserial].roadnum++]->next = &(Map->station[thisserial]);
				Map->station[thisserial].road[Map->station[thisserial].roadnum]->Busnumber = busnumber;
				Map->station[thisserial].road[Map->station[thisserial].roadnum++]->next = &(Map->station[lastserial]);
			}
			
			lastname = tempname;
			tempname = "";

		}
		file >> busnumber;
		//cout << endl;
		//cout << busnumber << ":" << endl;
		file.seekg(5, ios::cur);
		lastname = " ";
		if (!getline(file, buf1))
		{
			break;
		}
		j1 = 0;
		start = 1;
	}
	for (iter = stations.begin(); iter != stations.end(); iter++)
	{
		//cout << iter->first << "  " << iter->second << endl;
	}
	//cout << Map->stationnum;
	for (int i = 0; i < Map->stationnum; i++)
	{
		cout << Map->station[i].name << " ";
	}
}

void LeastRoutine(Map* Map, map<string, int>& stations, string firststation, string secondstation)
{
	LinkQueue q;
	InitQueue(q);
	map<string, int>::iterator iter1;
	map<string, int>::iterator iter2;
	map<string, int>::iterator iter3;
	iter1 = stations.find(firststation);
	iter2 = stations.find(secondstation);
	int serial = iter1->second;
	EnQueue(q, Map->station[serial]);
	int i = 0;
	Station e;
	int word = 0;
	Map->station[serial].IsSigned = true;
	while (!QueueEmpty(q))
	{
		while (i < Map->station[serial].roadnum)
		{
			if (Map->station[serial].road[i]->next->IsSigned == false)
			{
				if (Map->station[serial].road[i]->next->name != secondstation)
				{
					Map->station[serial].road[i]->next->IsSigned = true;
					Map->station[serial].road[i]->next->laststation = &(Map->station[serial]);
					EnQueue(q, *(Map->station[serial].road[i]->next));
				}
				else
				{
					Map->station[serial].road[i]->next->IsSigned = true;
					Map->station[serial].road[i]->next->laststation = &(Map->station[serial]);
					word = 1;
					break;
				}
				
			}
			i++;
		}
		if (word == 0)
		{
			i = 0;
			DeQueue(q, e);
			iter3 = stations.find(e.name);
			serial = iter3->second;
		}
		else if (word == 1)
		{
			vector<Station> station_vec;
			e = *(Map->station[serial].road[i]->next);
			while (e.laststation != NULL)
			{
				station_vec.push_back(e);
				iter3 = stations.find(e.laststation->name);
				e = Map->station[iter3->second];
			}
			station_vec.push_back(e);
			for (int i = station_vec.size() - 1; i > 0; i--)
			{
				cout << station_vec[i].name  << "-->";
			}
			cout << station_vec[0].name  << endl;
			break;
		}
	}
	if (word == 0)
	{
		cout << "这两站之间不存在可乘坐的公交路线" << endl;
	}
}

void SearchSameLine(LinkQueue& q, Map*& Map, map<string, int>& stations, string firststation, string secondstation, int serial, bool& IsFind, int busnumber, int& expectedserial, int trueserial)
{
	for (int j = 0; j < Map->station[serial].roadnum; j++)
	{
		if (IsFind == true)
		{
			break;
		}
		if (Map->station[serial].name == secondstation)
		{
			IsFind = true;
			expectedserial = serial;
			return;

		}
		if ((Map->station[serial].road[j]->Busnumber == busnumber))
		{
			map<string, int>::iterator iter;
			iter = stations.find(Map->station[serial].road[j]->next->name);
			if (iter != stations.end())
			{
				if (Map->station[serial].road[j]->next->IsSigned == false)
				{
					EnQueue(q, *(Map->station[serial].road[j]->next));
					if (Map->station[iter->second].laststation == NULL)
					{
						Map->station[iter->second].laststation = &(Map->station[trueserial]);
					}
					Map->station[serial].road[j]->next->IsSigned = true;
				}
				if ((Map->station[serial].road[j]->next->StackSigned == false))
				{
					Map->station[serial].road[j]->next->StackSigned = true;
					SearchSameLine(q, Map, stations, firststation, secondstation, iter->second, IsFind, busnumber, expectedserial, trueserial);
				}
				
			
			}
			
		}
	}
}
void LeastStationsChanged(Map* Map, map<string, int>& stations, string firststation, string secondstation)
{
	LinkQueue q;
	InitQueue(q);
	map<string, int>::iterator iter1;
	map<string, int>::iterator iter2;
	map<string, int>::iterator iter3;
	map<string, int>::iterator iter;
	iter1 = stations.find(firststation);
	iter2 = stations.find(secondstation);
	int serial = iter1->second;
	EnQueue(q, Map->station[serial]);
	Map->station[serial].IsSigned = true;
	int a[1000];
	memset(a, 0, sizeof(int) * 1000);
	bool IsFind = false;
	int busnumber;
	int expectedserial = -1;
	//busnumber = Map->station[serial].road[0]->Busnumber;
	Station e  = Map->station[serial];
	int t = 0;
	while (1)
	{
		for (int i = 0; i < Map->station[serial].roadnum; i++)//寻找下一个同一线路的节点
		{
			iter = stations.find(e.name);
			serial = iter->second;
			busnumber = Map->station[serial].road[i]->Busnumber;
			iter = stations.find(Map->station[serial].name);
			iter3 = stations.find(Map->station[serial].road[i]->next->name);//找到下一个车站在station数组的位置
			if (iter3 != stations.end())
			{
				if (Map->station[serial].road[i]->next->IsSigned == false)
				{
					EnQueue(q, *(Map->station[serial].road[i]->next));
					if (Map->station[iter3->second].laststation == NULL)
					{
						Map->station[iter3->second].laststation = &(Map->station[serial]);
					}
					Map->station[serial].road[i]->next->IsSigned = true;
				}
				//找所在的某一路的所有合法站点
				Map->station[serial].road[i]->next->StackSigned = true;
				SearchSameLine(q, Map, stations, firststation, secondstation, iter3->second, IsFind, busnumber, expectedserial, iter->second);
			}
			for (int i = 0; i < Map->stationnum; i++)
			{
				Map->station[i].StackSigned = false;
			}
			if (IsFind == true)
			{
				break;
			}
		}
		if (IsFind == true)
		{
			vector<Station> leaststation_vec;
			Station s;
			s = Map->station[expectedserial];
			while (s.laststation != NULL)
			{
				leaststation_vec.push_back(s);
				iter3 = stations.find(s.laststation->name);
				s = Map->station[iter3->second];
			}
			//iter2 = stations.find("岔路口站");
			cout << "共需换乘" << leaststation_vec.size() << "次" << endl;
			cout << firststation << "(" << "( 起点 ) -->";
			for (int i = leaststation_vec.size() - 1; i > 0; i--)
			{
				cout << leaststation_vec[i].name  << "-->";

			}
			cout << leaststation_vec[0].name << "( 终点 )";
			break;
			
		}
		DeQueue(q, e);
		t++;
	}

}
int main()
{
	Map* M = new Map;
	map<string, int>stations;
	ReadFile(M, stations);
	string firststation;
	string secondstation;
	map<string, int>::iterator iter;
	cout << "请输入要查询的两个站点" << endl;
	cin >> firststation;
	cin.ignore();
	if (stations.find(firststation) == stations.end())
	{
		cout << "无此站点" << endl;
		exit(1);
	}
	cin >> secondstation;
	cin.ignore();
	if (stations.find(secondstation) == stations.end())
	{
		cout << "无此站点" << endl;
		exit(1);
	}
	LeastRoutine(M, stations, firststation, secondstation);
	for (int i = 0; i < M->stationnum; i++)
	{
		M->station[i].IsSigned = false;
		M->station[i].laststation = NULL;
	}
	LeastStationsChanged(M, stations, firststation, secondstation);
}