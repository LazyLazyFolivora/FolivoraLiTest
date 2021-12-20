// @author: Folivora Li
// @copyright: Folivora Li

/*19����2��Hash��Ӧ�� ��ѡ���� �����ң�
[��������]
���ɢ�б�ʵ��VIP�ͻ����򡣶����֤�Ž���Hash, ͨ���Գ˿�ĳʱ����ڵĳ˻�Ƶ�ʡ�
�����ͳ�ƣ�����VIP�ͻ��� 
[����Ҫ��]
��1�� ��ÿ����¼��������������֤���루�鹹��λ���ͱ����������ʵһ�¼��ɣ���
����������š��������ڡ���̡� 
��2�� ���ļ��������¼�������֤����Ϊ�ؼ��ֽ���ɢ�б� 
��3�� �ֱ���ÿ��Ŷ�ַ������ѡ�����ƶ�ַ������������ַ���ַ��������ͻ��
��ʾ������ͻ�Ĵ�����ÿ���н����ͻ�����ض�λ�Ĵ�����
��4����¼����������100�����ϡ�
��5�� �Ӽ�¼��ʵ�ֳ˿ͳ˻�Ƶ�ʡ������ͳ�ƣ��Ӷ�����VIP�ͻ���*/
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

class FindID	//����find(),��find�ܸ������֤�鵽��Ϣ
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
		//tostring�ǵ���ת�����֣�ǿ��ת����acsii��
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
	cout << "д���ļ���ɣ�" << endl;
	
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
//���Ŷ�ַ��
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
		if (map[stoi(temp)].person == NULL)	//stoi���ַ���ת��Ϊ����
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
	cout << "������ͻ����:"<< count << endl;
}
//����ַ��
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
		if (map[stoi(temp)].person == NULL)	//stoi���ַ���ת��Ϊ����
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
	cout << "������ͻ����:" << count << endl;
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
	cout << "VIP�У�";
	for (int i = 0; i < passenger.size(); i++)
	{
		if (passenger[i].IsVIP == true)
		{
			cout << passenger[i].name << " " << "�˻�����:" << passenger[i].time << " " << "�ۼƳ˻����룺" << passenger[i].distance << endl;
		}
	}

}