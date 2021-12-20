/*3�����׹���ϵͳ��������������
[��������]
ʵ�־������й��ܵļ��׹���ϵͳ��
[����Ҫ��]
��1�������ļ��Դ����������и���Ա����Ϣ����Ա����Ϣ�о�Ӧ�����������ݣ�
�������������ڡ���񡢵�ַ�����ڷ��������ڣ���������������Ҳ�ɸ���������Ϣ��
�����Ǳ���ġ�
��2��ʵ�����ݵ��ļ��洢�Ͷ�ȡ��
��3����ͼ�η�ʽ��ʾ���ס�
��4����ʾ��n �������˵���Ϣ��
��5������������ѯ�������Ա��Ϣ�������䱾�ˡ����ס����ӵ���Ϣ����
��6�����ճ������ڲ�ѯ��Ա������
��7����������������ȷ�����ϵ��
��8��ĳ��Ա��Ӻ��ӡ�
��9��ɾ��ĳ��Ա�����仹�к������һ��ɾ������
��10���޸�ĳ��Ա��Ϣ��
��11��Ҫ��������40����Ա�����ݣ��Խ�Ϊֱ�۵ķ�ʽ��ʾ��������ṩ�ĸ���ʽ�Ա��顣
��12������Ҫ���к������ʾ��ÿ�����ܿ��������˵���������ʾ�����������صĹ���Ҫ��
��13���洢�ṹ������ϵͳ����Ҫ��������ƣ�����Ҫ���������Ҫ�洢�������ļ��С�
�������ݣ�Ҫ��ʹ��1��ȫ���Ϸ����ݣ�2���ֲ��Ƿ����ݡ����г�����ԣ��Ա�֤������ȶ���*/
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
typedef struct {
	int year;
	int month;
	int day;
}Date;
typedef struct {
	string name;		//����
	int depth;			//����
	Date birthday;		//��������
	string IsMarried;	//�Ƿ��ѻ�
	string address;		//��ַ
	string IsAlive;		//�Ƿ�����
	Date deathday;		//��������
	string remarks;		//��ע
	
}PersonMessage;

typedef struct treenode {
	PersonMessage person;
	treenode* leftchild;		//����
	treenode* rightbrother;		//���ֵ�
	treenode* parent;			//���ڵ�
	int depth;					//����
}treenode;

void PrintMessage(treenode* target);

//�����ݴ浽����(��ȡ����)
void CreateGengalogyFile(treenode*& root,fstream& file,int depthbefore)
{ 
	if (file.eof())
	{
		return;
	}
	int depth;
	file >> depth;
	root->person.depth = depth;
	root->depth = depth;
	file >> root->person.name;
	file >> root->person.birthday.year;
	file >> root->person.birthday.month;
	file >> root->person.birthday.day;
	file >> root->person.IsMarried;
	file >> root->person.address;
	file >> root->person.IsAlive;
	file >> root->person.deathday.year;
	file >> root->person.deathday.month;
	file >> root->person.deathday.day;
	file >> root->person.remarks;
	int nextdepth;
	fstream f;
	f.open("D:\\gengalogy.txt", ios::in);
	if (f.fail())
	{
		cout << "error1!" << endl;
		exit(1);
	}
	f.seekg(file.tellg());
	
	if (file.eof())
	{
		return;
	}
	f >> nextdepth;
	f.close();
	if (nextdepth > depth)
	{
		root->leftchild = new treenode;
		root->leftchild->leftchild = NULL;
		root->leftchild->rightbrother = NULL;
		CreateGengalogyFile(root->leftchild, file, depth);
	}
	f.open("D:\\gengalogy.txt", ios::in);
	if (f.fail())
	{
		cout << "error1!" << endl;
		exit(1);
	}
	f.seekg(file.tellg());

	if (file.eof())
	{
		return;
	}
	f >> nextdepth;
	f.close();
	if (nextdepth == depth)
	{
		root->rightbrother = new treenode;
		root->rightbrother->leftchild = NULL;
		root->rightbrother->rightbrother = NULL;
		CreateGengalogyFile(root->rightbrother, file, depth);
	}
}

//���ø��ڵ�
void SetParent(treenode*& root, treenode*& parent)
{
	root->parent = parent;
	if (root->leftchild != NULL)
	{
		SetParent(root->leftchild, root);
	}
	if (root->rightbrother != NULL)
	{
		SetParent(root->rightbrother, parent);
	}
	
}

//��ӡ�������г�Ա��Ϣ
void PrintAllMessage(treenode* root)
{
	if (root != NULL)
	{
		PrintMessage(root);
	}
	if (root->leftchild != NULL)
	{
		PrintAllMessage(root->leftchild);
	}
	if (root->rightbrother != NULL)
	{
		PrintAllMessage(root->rightbrother);
	}
}

//��ӡ����ĳ��Ա��Ϣ
void PrintMessage(treenode* target)
{
	cout << "����:" << target->person.name<<"  ";
	cout << "�����е�" << target->person.depth << "����" << "  ";
	if (target->person.IsMarried == "�ѻ�")
	{
		cout << "����״��:�ѻ�" << endl;

	}
	else if (target->person.IsMarried == "δ��")
	{
		cout << "����״��:δ��" << endl;
	}
	cout << "��������:" << target->person.birthday.year << "��" << target->person.birthday.month << "��" << target->person.birthday.day << "��" << endl;
	cout << "��ַ:" << target->person.address << endl;
	if (target->person.IsAlive == "����")
	{
		cout << "��������:" << target->person.deathday.year << "��" << target->person.deathday.month << "��" << target->person.deathday.day << "��" << endl;
	}
	cout << "��ע:" << target->person.remarks << endl;
	cout << endl;
	cout << endl;
}

//��ӡĳ���Ա��Ϣ
void PrintDepthMessage(treenode* root, int depth)
{
	if (root->person.depth == depth)
	{
		PrintMessage(root);
	}
	if (root->leftchild != NULL)
	{
		PrintDepthMessage(root->leftchild, depth);
	}
	if (root->rightbrother != NULL)
	{
		PrintDepthMessage(root->rightbrother, depth);
	}
}

//����ĳ��������Ϣ
void SearchName(treenode* root, string name,bool& IsFind)
{
	if (name == root->person.name)
	{
		IsFind = true;
		cout << "������Ϣ:" << endl;
		PrintMessage(root);
		if (root->parent != NULL)
		{
			cout << "�丸����Ϣ:" << endl;
			PrintMessage(root->parent);
		}
		treenode* p = root;
		int childrennum = 0;
		if (p->leftchild != NULL)
		{
			cout << "�亢��" << ++childrennum << "��Ϣ:" << endl;
			p = p->leftchild;
			PrintMessage(p);
			while (p->rightbrother != NULL)
			{
				cout << "�亢��" << ++childrennum << "��Ϣ:" << endl;
				p = p->rightbrother;
				PrintMessage(p);
			}
		}
	}
	if (root->leftchild != NULL)
	{
		SearchName(root->leftchild, name, IsFind);
	}
	if (root->rightbrother != NULL)
	{
		SearchName(root->rightbrother, name, IsFind);
	}
}

//�����������Ա��Ϣ
void PrintMessageByName(treenode* root)
{
	string name;
	cin >> name;
	cin.ignore();
	bool IsFind = false;
	SearchName(root, name, IsFind);
	if (IsFind == false)
	{
		cout << "�������޴����ֵ���!" << endl;
	}
}

//����ĳ���ڵ���Ϣ
void SearchBirthday(treenode* root, Date birthday,bool& IsFind)
{
	if ((birthday.day == root->person.birthday.day)&& (birthday.month == root->person.birthday.month)&& (birthday.year == root->person.birthday.year))
	{
		IsFind = true;
		cout << "������Ϣ:" << endl;
		PrintMessage(root);
		if (root->parent != NULL)
		{
			cout << "�丸����Ϣ:" << endl;
			PrintMessage(root->parent);
		}
		treenode* p = root;
		int childrennum = 0;
		if (p->leftchild != NULL)
		{
			cout << "�亢��" << ++childrennum << "��Ϣ:" << endl;
			p = p->leftchild;
			PrintMessage(p);
			while (p->rightbrother != NULL)
			{
				cout << "�亢��" << ++childrennum << "��Ϣ:" << endl;
				p = p->rightbrother;
				PrintMessage(p);
			}
		}
	}
	if (root->leftchild != NULL)
	{
		SearchBirthday(root->leftchild, birthday, IsFind);
	}
	if (root->rightbrother != NULL)
	{
		SearchBirthday(root->rightbrother, birthday, IsFind);
	}
}

//���������������Ա��Ϣ
void PrintMessageByBirthday(treenode* root)
{
	int year;
	int month;
	int day;
	cout << "��������" << endl;
	cin >> year;
	cin.ignore();
	cout << "��������" << endl;
	cin >> month;
	cin.ignore();
	cout << "��������" << endl;
	cin >> day;
	cin.ignore();
	Date birthday;
	birthday.year = year;
	birthday.month = month;
	birthday.day = day;
	bool IsFind = false;
	SearchBirthday(root, birthday, IsFind);
	if (IsFind == false)
	{
		cout << "�������޴˳������ڵ���!" << endl;
	}
}

void ReturnTreenodeByName(treenode*& root, string name,treenode*& target)
{
	if (root->person.name == name)
	{
		target = root;
	}
	if (root->leftchild != NULL)
	{
		ReturnTreenodeByName(root->leftchild, name, target);
	}
	if (root->rightbrother != NULL)
	{
		ReturnTreenodeByName(root->rightbrother, name, target);
	}
}

//�ж����˹�ϵ
void JudgeRalationship(treenode* root)
{
	string name1;
	string name2;
	cout << "���������������˵�����" << endl;
	cin >> name1;
	cin.ignore();
	cin >> name2;
	cin.ignore();
	treenode* Person1 = NULL;
	treenode* Person2 = NULL;
	ReturnTreenodeByName(root, name1, Person1);
	ReturnTreenodeByName(root, name2, Person2);
	if (Person1 == NULL)
	{
		cout << "������û��" << name1 << "�����" << endl;
		return;
	}
	if (Person2 == NULL)
	{
		cout << "������û��" << name2 << "�����" << endl;
		return;
	}
	int depth1 = Person1->person.depth;
	int depth2 = Person2->person.depth;
	if (depth1 == depth2)
	{
		cout << name1 << "��" << name2 << "Ϊ�ֵܹ�ϵ" << endl;
		return;
	}
	if (depth1 - depth2 == -1)
	{
		if (Person2->parent == Person1)
		{
			cout << name1 << "��" << name2 << "�ĸ���" << endl;
			return;
		}
		else
		{
			cout<< name1 << "��" << name2 << "������" << endl;
		}
	}
	if (depth1 - depth2 == 1)
	{
		if (Person1->parent == Person2)
		{
			cout << name2 << "��" << name1 << "�ĸ���" << endl;
			return;
		}
		else
		{
			cout << name2 << "��" << name1 << "������" << endl;
			return;
		}
	}
	if (depth1 - depth2 == -2)
	{
		cout << name1 << "��" << name2 << "��үү" << endl;
		return;
		
	}
	if (depth1 - depth2 == 2)
	{
		cout << name2 << "��" << name1 << "��үү" << endl;
		return;

	}
	if (depth1 - depth2 < -2)
	{
		cout << name1 << "��" << name2 << "������" << endl;
		return;

	}
	if (depth2 - depth1 < -2)
	{
		cout << name2 << "��" << name1 << "������" << endl;
		return;

	}
	

}

void ReturnTreenodeByNameAndBirthday(treenode*& root, string name, treenode*& target, Date birthday)
{
	if ((root->person.name == name) && (root->person.birthday.year == birthday.year) && (root->person.birthday.month == birthday.month) && (root->person.birthday.day == birthday.day))
	{
		target = root;
	}
	if (root->leftchild != NULL)
	{
		ReturnTreenodeByNameAndBirthday(root->leftchild, name, target, birthday);
	}
	if (root->rightbrother != NULL)
	{
		ReturnTreenodeByNameAndBirthday(root->rightbrother, name, target, birthday);
	}
}
//��Ӻ���
void InsertChild(treenode*& root)
{
	string name;
	Date birthday;
	cout << "������Ҫ��Ӻ��ӳ�Ա������" << endl;
	cin >> name;
	cin.ignore();
	cout << "������ó�Ա������" << endl;
	cin >> birthday.year;
	cin.ignore();
	cin >> birthday.month;
	cin.ignore();
	cin >> birthday.day;
	cin.ignore();
	treenode* person = NULL;
	ReturnTreenodeByNameAndBirthday(root, name, person, birthday);
	if (person == NULL)
	{
		cout << "������Ϣ����!" << endl;
		return;
	}
	treenode* child = new treenode;
	child->depth = person->depth + 1;
	cout << "����������:" << endl;
	cin >> child->person.name;
	cin.ignore();
	cout << "����������(��,��,��):" << endl;
	cin >> child->person.birthday.year;
	cin.ignore();
	cin >> child->person.birthday.month;
	cin.ignore();
	cin >> child->person.birthday.day;
	cin.ignore();
	cout << "�������ַ" << endl;
	cin >> child->person.address;
	child->person.depth = child->depth;
	int IsMarried;
	cout << "���������״��,�ѻ���0��δ����1" << endl;
	cin >> IsMarried;
	cin.ignore();
	int word = 1;
	while (word)
	{
		if (IsMarried == 0)
		{
			child->person.IsMarried = "�ѻ�";
			word = 0;
		}
		else if (IsMarried == 1)
		{
			child->person.IsMarried = "δ��";
			word = 0;
		}
		else
		{
			cout << "�������ݷǷ�,����������" << endl;
			cin >> IsMarried;
		}
	}
	word = 1;
	cout << "�����Ƿ�������������0����ȥ����1" << endl;
	int IsAlive;
	cin >> IsAlive;
	cin.ignore();
	while (word)
	{
		if (IsAlive == 0)
		{
			child->person.IsAlive = "����";
			child->person.deathday.day = 0;
			child->person.deathday.month = 0;
			child->person.deathday.year = 0;
			word = 0;
		}
		else if (IsAlive == 1)
		{
			child->person.IsAlive = "����";
			word = 0;
			cout << "������ȥ������(��,��,��):" << endl;
			cin >> child->person.deathday.year;
			cin.ignore();
			cin >> child->person.deathday.month;
			cin.ignore();
			cin >> child->person.deathday.day;
			cin.ignore();
		}
		else
		{
			cout << "�������ݷǷ�,����������" << endl;
			cin >> IsAlive;
		}
		cout << "�����뱸ע" << endl;
		cin >> child->person.remarks;
		cin.ignore();
	}
	if (person->leftchild == NULL) 
	{
		person->leftchild = child;
		child->parent = person;
		child->leftchild = NULL;
		child->rightbrother = NULL;
		child->depth = person->depth + 1;
		
	}
	else
	{
		treenode* p = person->leftchild;
		while (p->rightbrother != NULL)
		{
			p = p->rightbrother;
			
		}
		p->rightbrother = child;
		child->parent = person;
		child->leftchild = NULL;
		child->rightbrother = NULL;
		child->depth = person->depth + 1;


	}

}

//ɾ��ĳ��Ա
void DeleteMember(treenode*& root)
{
	string name;
	Date birthday;
	cout << "������ó�Ա������" << endl;
	cin >> name;
	cin.ignore();
	cout << "������ó�Ա������" << endl;
	cin >> birthday.year;
	cin.ignore();
	cin >> birthday.month;
	cin.ignore();
	cin >> birthday.day;
	cin.ignore();
	treenode* person = NULL;
	ReturnTreenodeByNameAndBirthday(root, name, person, birthday);
	if (person == NULL)
	{
		cout << "������Ϣ����!" << endl;
		return;
	}
	if (person->parent != NULL)
	{
		treenode* p = person->parent;
		if (p->leftchild == person)
		{
			p->leftchild = person->rightbrother;
			delete person;
			person = NULL;
		}
		else
		{
			treenode* p1 = p->leftchild;
			while (p1->rightbrother != p)
			{
				p1 = p1->rightbrother;
			}
			p1->rightbrother = person->rightbrother;
			delete person;
			person = NULL;

		}
	}
	else
	{
		cout << "��һ�����޷�ɾ��!" << endl;
	}
}

//�޸�ĳ��Ա��Ϣ
void ModifyMember(treenode*& root)
{
	string name;
	Date birthday;
	cout << "������ó�Ա������" << endl;
	cin >> name;
	cin.ignore();
	cout << "������ó�Ա������" << endl;
	cin >> birthday.year;
	cin.ignore();
	cin >> birthday.month;
	cin.ignore();
	cin >> birthday.day;
	cin.ignore();
	treenode* person = NULL;
	ReturnTreenodeByNameAndBirthday(root, name, person, birthday);
	if (person == NULL)
	{
		cout << "������Ϣ����!" << endl;
		return;
	}
	cout << "�밴����ָ���޸���Ϣ��" << endl;
	cout << "����������:" << endl;
	cin >> person->person.name;
	cin.ignore();
	cout << "����������(��,��,��):" << endl;
	cin >> person->person.birthday.year;
	cin.ignore();
	cin >> person->person.birthday.month;
	cin.ignore();
	cin >> person->person.birthday.day;
	cin.ignore();
	cout << "�������ַ" << endl;
	cin >> person->person.address;
	person->person.depth = person->depth;
	int IsMarried;
	cout << "���������״��,�ѻ���0��δ����1" << endl;
	cin >> IsMarried;
	cin.ignore();
	int word = 1;
	while (word)
	{
		if (IsMarried == 0)
		{
			person->person.IsMarried = "�ѻ�";
			word = 0;
		}
		else if (IsMarried == 1)
		{
			person->person.IsMarried = "δ��";
			word = 0;
		}
		else
		{
			cout << "�������ݷǷ�,����������" << endl;
			cin >> IsMarried;
		}
	}
	word = 1;
	cout << "�����Ƿ�������������0����ȥ����1" << endl;
	int IsAlive;
	cin >> IsAlive;
	cin.ignore();
	cout << "�����뱸ע" << endl;
	cin >> person->person.remarks;
	cin.ignore();
	while (word)
	{
		if (IsAlive == 0)
		{
			person->person.IsAlive = "����";
			person->person.deathday.day = 0;
			person->person.deathday.month = 0;
			person->person.deathday.year = 0;
			word = 0;
		}
		else if (IsAlive == 1)
		{
			person->person.IsAlive = "����";
			word = 0;
			cout << "������ȥ������(��,��,��):" << endl;
			cin >> person->person.deathday.year;
			cin.ignore();
			cin >> person->person.deathday.month;
			cin.ignore();
			cin >> person->person.deathday.day;
			cin.ignore();
		}
		else
		{
			cout << "�������ݷǷ�,����������" << endl;
			cin >> IsAlive;
		}
	}
	
}

//�������������Ԫ�ش����ļ���
void SaveFile(treenode* root, fstream& file)
{
	if (root != NULL)
	{
		file << root->person.depth;
		file << " ";
		file << root->person.name;
		file << " ";
		file << root->person.birthday.year;
		file << " ";
		file << root->person.birthday.month;
		file << " ";
		file << root->person.birthday.day;
		file << " ";
		file << root->person.IsMarried;
		file << " ";
		file << root->person.address;
		file << " ";
		file << root->person.IsAlive;
		file << " ";
		file << root->person.deathday.year;
		file << " ";
		file << root->person.deathday.month;
		file << " ";
		file << root->person.deathday.day;
		file << " ";
		file << root->person.remarks;
		file << '\n';
	}
	if (root->leftchild != NULL)
	{
		SaveFile(root->leftchild, file);

	}
	if (root->rightbrother != NULL)
	{
		SaveFile(root->rightbrother, file);
	}
}

int main()
{
	fstream file1;
	file1.open("D:\\gengalogy.txt", ios::in);
	if (file1.fail())
	{
		cout << "error!"<< endl;
		exit(1);
	}
	treenode* root = new treenode;
	CreateGengalogyFile(root, file1, 0);
	file1.close();
	treenode* parent = NULL;
	SetParent(root, parent);
	cout << "----------------------------��ӭ������׹���ϵͳ--------------------------------" << endl;
	
	while (1)
	{
		cout << "--------------------------------�˵�----------------------------------" << endl;
		cout << "1.��ѯ��n�������˵���Ϣ" << endl;
		cout << "2.����������ѯ��Ա��Ϣ" << endl;
		cout << "3.���ճ������ڲ�ѯ��Ա��Ϣ" << endl;
		cout << "4.��ѯ���˹�ϵ" << endl;
		cout << "5.Ϊĳ��Ա��Ӻ���" << endl;
		cout << "6.ɾ��ĳ��Ա������" << endl;
		cout << "7.�޸�ĳ��Ա��Ϣ" << endl;
		cout << "8.������г�Ա��Ϣ" << endl;
		cout << "9.�˳�����" << endl;
		int choice;
		cout << "������ѡ��" << endl;
		cin >> choice;
		cin.ignore();
		switch (choice)
		{
			case 1:
			{
				cout << "������Ҫ��ѯ�Ĵ���" << endl;
				int depth;
				cin >> depth;
				cin.ignore();
				PrintDepthMessage(root, depth);
				break;
			}
			case 2:
			{
				PrintMessageByName(root);
				break;
			}
			case 3:
			{
				PrintMessageByBirthday(root);
				break;
			}
			case 4:
			{
				JudgeRalationship(root);
				break;
			}
			case 5:
			{
				file1.open("D:\\gengalogy.txt", ios::out);
				if (file1.fail())
				{
					cout << "error!" << endl;
					exit(1);
				}
				InsertChild(root);
				SaveFile(root, file1);
				file1.close();
				break;
			}
			case 6:
			{
				file1.open("D:\\gengalogy.txt", ios::out);
				if (file1.fail())
				{
					cout << "error!" << endl;
					exit(1);
				}
				DeleteMember(root);
				SaveFile(root, file1);
				file1.close();
				break;
			}
			case 7:
			{
				file1.open("D:\\gengalogy.txt", ios::out);
				if (file1.fail())
				{
					cout << "error!" << endl;
					exit(1);
				}
				ModifyMember(root);
				SaveFile(root, file1);
				file1.close();
				break;
			}
			case 8:
			{
				PrintAllMessage(root);
			}
			case 9:
			{
				exit(1);
			}
			default:
			{
				cout << "�������ַǷ�������������!" << endl;
				break;
			}
		}
	}
	
}