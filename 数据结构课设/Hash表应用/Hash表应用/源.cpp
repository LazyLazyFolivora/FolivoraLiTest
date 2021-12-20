// @author: Folivora Li
// @copyright: Folivora Li

/*19、【2】Hash表应用 （选做） （查找）
[问题描述]
设计散列表实现VIP客户发掘。对身份证号进行Hash, 通过对乘客某时间段内的乘机频率、
里程数统计，发掘VIP客户。 
[基本要求]
（1） 设每个记录有下列数据项：身份证号码（虚构，位数和编码规则与真实一致即可）、
姓名、航班号、航班日期、里程。 
（2） 从文件输入各记录，以身份证号码为关键字建立散列表。 
（3） 分别采用开放定址（自行选择和设计定址方案）和链地址两种方案解决冲突；
显示发生冲突的次数、每次中解决冲突进行重定位的次数。
（4）记录条数至少在100条以上。
（5） 从记录中实现乘客乘机频率、里程数统计，从而发掘VIP客户。*/
#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include <algorithm>
using namespace std;
typedef struct {
	int year;
	int month;
	int day;
}Date;

typedef struct {
	string ID;
	string name;
	string FlightID;
	Date date;
	int distance;
	int time = 1;
	bool IsVIP = false;
}Passenger;
typedef struct PassengerLink{
	string ID;
	string name;
	string FlightID;
	Date date;
	int distance;
	PassengerLink* next = NULL;
}PassengerLink;

typedef struct {
	Passenger* person = NULL;
	int conflictiontime = 0;
}Hashmap;


typedef struct {
	PassengerLink* person = NULL;
	
}
Hashmap_Link;

class FindID	//重载find(),让find能根据身份证查到信息
{
private:
	string ID;
public:
	FindID(const string& ID)
	{
		this->ID = ID;
	}
	bool operator()(vector<Passenger>::value_type& Id)
	{
		return Id.ID == this->ID;
	}
};
void CreateRandomData()
{
	fstream file;
	file.open("D:\\hash.txt", ios::out);
	if (file.fail())
	{
		cout << "error" << endl;
		exit(1);
	}
	int count = 0;
	while (count < 200)
	{
		Passenger passenger;
		int temp;
		for (int i = 0; i < 18; i++)
		{
			srand(time(NULL) * (i + 1) * (count + 1));
			if (i == 6)
			{
				temp = 1;
			}
			else if (i == 7)
			{
				temp = 9;
			}
			else if (i == 10)
			{
				temp = 0;
			}
			else
			{
				temp = rand() % 10;
			}
			passenger.ID += to_string(temp);
		}
		//tostring是单纯转换数字，强制转换是acsii码
		for (int i = 0; i < 3; i++)
		{
			srand(time(NULL) * (i + 1) * (count + 1));
			passenger.name += char(rand() % 25 + 66);
		}
		for (int i = 0; i < 3; i++)
		{
			srand(time(NULL) * (i + 1) * (count + 1));
			passenger.FlightID += to_string(rand() % 10);
		}
		srand(time(NULL) * (count + 1));
		int year;
		int month;
		int day;
		year = rand() % 2 + 2019;
		month = rand() % 12 + 1;
		day = rand() % 28 + 1;
		int distance;
		distance = rand() % 1500 + 500;
		passenger.date.year = year;
		passenger.date.month = month;
		passenger.date.day = day;
		passenger.distance = distance;
		file << passenger.ID << " ";
		file << passenger.name << " ";
		file << passenger.FlightID << " ";
		file << passenger.date.year << " ";
		file << passenger.date.month << " ";
		file << passenger.date.day << " ";
		file << passenger.distance << " \n";

		count++;
	}
	cout << "写入文件完成！" << endl;
	
}
void ReadFile(vector<Passenger>& passenger)
{
	fstream file;
	vector<Passenger>::iterator iter;
	file.open("D:\\hash.txt", ios::in);
	if (file.fail())
	{
		cout << "error" << endl;
		exit(1);
	}
	int count = 0;
	while (!file.eof())
	{
		Passenger p;
		file >> p.ID;
		file >> p.name;
		file >> p.FlightID;
		file >> p.date.year;
		file >> p.date.month;
		file >> p.date.day;
		file >> p.distance;
		if (file.eof())
		{
			break;
		}
		iter = find_if(passenger.begin(), passenger.end(), FindID(p.ID));
		if (iter == passenger.end())
		{
			passenger.push_back(p);
		}
		else
		{
			cout << "111" << endl;
			iter->time++;
			iter->distance += p.distance;
		}

	}
}
//开放定址法
void Createmap(Hashmap map[10000],vector<Passenger>& passenger)
{
	int count = 0;
	string temp;
	
	for (int i = 0; i < passenger.size(); i++)
	{
		temp += passenger[i].ID[5];
		temp += passenger[i].ID[9];
		temp += passenger[i].ID[13];
		temp += passenger[i].ID[17];
		//cout << stoi(temp) << " ";
		if (map[stoi(temp)].person == NULL)	//stoi将字符串转化为数字
		{
			map[stoi(temp)].person = &passenger[i];
		}
		else
		{
			int serial = stoi(temp);
			while (map[serial].person != NULL)
			{
				//cout << serial << endl;
				serial++;
				count++;
			}
			map[serial].person = &passenger[i];
			map[serial].conflictiontime = serial - stoi(temp);
		}
		temp = "";
	}
	cout << "发生冲突次数:"<< count << endl;
}
//链地址法
void CreateLinkmap(Hashmap_Link map[10000], vector<PassengerLink>& passenger)
{
	int count = 0;
	string temp;
	for (int i = 0; i < passenger.size(); i++)
	{
		temp += passenger[i].ID[5];
		temp += passenger[i].ID[9];
		temp += passenger[i].ID[13];
		temp += passenger[i].ID[17];
		cout << stoi(temp) <<" ";
		if (map[stoi(temp)].person == NULL)	//stoi将字符串转化为数字
		{
			map[stoi(temp)].person = &passenger[i];
		}
		else
		{
			PassengerLink* p = map[stoi(temp)].person;
			while (p->next != NULL)
			{
				count++;
				p = p->next;
			}
			PassengerLink* q = new PassengerLink;
			q = &passenger[i];
			q->next = NULL;
			p->next = q;
			count++;

		}
		temp = "";
	}
	cout << "发生冲突次数:" << count << endl;
}
int main()
{

	//CreateRandomData();
	vector<Passenger> passenger;
	vector<PassengerLink> passengerlink;
	ReadFile(passenger);
	for (int i = 0; i < passenger.size(); i++)
	{
		PassengerLink p;
		p.name = passenger[i].name;
		p.ID = passenger[i].ID;
		p.FlightID = passenger[i].FlightID;
		p.date = passenger[i].date;
		p.distance = passenger[i].distance;
		p.next = NULL;
		passengerlink.push_back(p);
	}
	
	for (int i = 0; i < passenger.size(); i++)
	{
		cout << passenger[i].ID;
		cout << "  ";
		cout << passenger[i].name;
		cout << " ";
		cout << passenger[i].FlightID;
		cout << "  " << passenger[i].date.year << "-" << passenger[i].date.month << "-" << passenger[i].date.day << "  " << passenger[i].distance << endl;
	}
	for (int i = 0; i < passenger.size(); i++)
	{
		if ((passenger[i].distance > 3000) && (passenger[i].time >= 3))
		{
			passenger[i].IsVIP = true;
		}
	}
	Hashmap map[10000];
	Createmap(map, passenger);
	Hashmap_Link map_link[10000];
	cout << passengerlink.size() << endl;
	CreateLinkmap(map_link, passengerlink);
	cout << "VIP有：";
	for (int i = 0; i < passenger.size(); i++)
	{
		if (passenger[i].IsVIP == true)
		{
			cout << passenger[i].name << " " << "乘机次数:" << passenger[i].time << " " << "累计乘机距离：" << passenger[i].distance << endl;
		}
	}

}