/*3、家谱管理系统（必做）（树）
[问题描述]
实现具有下列功能的家谱管理系统。
[基本要求]
（1）输入文件以存放最初家谱中各成员的信息，成员的信息中均应包含以下内容：
姓名、出生日期、婚否、地址、健在否、死亡日期（若其已死亡），也可附加其它信息、
但不是必需的。
（2）实现数据的文件存储和读取。
（3）以图形方式显示家谱。
（4）显示第n 代所有人的信息。
（5）按照姓名查询，输出成员信息（包括其本人、父亲、孩子的信息）。
（6）按照出生日期查询成员名单。
（7）输入两人姓名，确定其关系。
（8）某成员添加孩子。
（9）删除某成员（若其还有后代，则一并删除）。
（10）修改某成员信息。
（11）要求建立至少40个成员的数据，以较为直观的方式显示结果，并提供文稿形式以便检查。
（12）界面要求：有合理的提示，每个功能可以设立菜单，根据提示，可以完成相关的功能要求。
（13）存储结构：根据系统功能要求自行设计，但是要求相关数据要存储在数据文件中。
测试数据：要求使用1、全部合法数据；2、局部非法数据。进行程序测试，以保证程序的稳定。*/
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
	string name;		//名字
	int depth;			//代数
	Date birthday;		//出生日期
	string IsMarried;	//是否已婚
	string address;		//地址
	string IsAlive;		//是否在世
	Date deathday;		//死亡日期
	string remarks;		//备注
	
}PersonMessage;

typedef struct treenode {
	PersonMessage person;
	treenode* leftchild;		//左孩子
	treenode* rightbrother;		//右兄弟
	treenode* parent;			//父节点
	int depth;					//代数
}treenode;

void PrintMessage(treenode* target);

//将数据存到树中(读取数据)
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

//设置父节点
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

//打印家谱所有成员信息
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

//打印家谱某成员信息
void PrintMessage(treenode* target)
{
	cout << "姓名:" << target->person.name<<"  ";
	cout << "家谱中第" << target->person.depth << "代人" << "  ";
	if (target->person.IsMarried == "已婚")
	{
		cout << "婚姻状况:已婚" << endl;

	}
	else if (target->person.IsMarried == "未婚")
	{
		cout << "婚姻状况:未婚" << endl;
	}
	cout << "出生日期:" << target->person.birthday.year << "年" << target->person.birthday.month << "月" << target->person.birthday.day << "日" << endl;
	cout << "地址:" << target->person.address << endl;
	if (target->person.IsAlive == "离世")
	{
		cout << "逝世日期:" << target->person.deathday.year << "年" << target->person.deathday.month << "月" << target->person.deathday.day << "日" << endl;
	}
	cout << "备注:" << target->person.remarks << endl;
	cout << endl;
	cout << endl;
}

//打印某层成员信息
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

//查找某姓名的信息
void SearchName(treenode* root, string name,bool& IsFind)
{
	if (name == root->person.name)
	{
		IsFind = true;
		cout << "此人信息:" << endl;
		PrintMessage(root);
		if (root->parent != NULL)
		{
			cout << "其父亲信息:" << endl;
			PrintMessage(root->parent);
		}
		treenode* p = root;
		int childrennum = 0;
		if (p->leftchild != NULL)
		{
			cout << "其孩子" << ++childrennum << "信息:" << endl;
			p = p->leftchild;
			PrintMessage(p);
			while (p->rightbrother != NULL)
			{
				cout << "其孩子" << ++childrennum << "信息:" << endl;
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

//按姓名输出成员信息
void PrintMessageByName(treenode* root)
{
	string name;
	cin >> name;
	cin.ignore();
	bool IsFind = false;
	SearchName(root, name, IsFind);
	if (IsFind == false)
	{
		cout << "家谱中无此名字的人!" << endl;
	}
}

//查找某日期的信息
void SearchBirthday(treenode* root, Date birthday,bool& IsFind)
{
	if ((birthday.day == root->person.birthday.day)&& (birthday.month == root->person.birthday.month)&& (birthday.year == root->person.birthday.year))
	{
		IsFind = true;
		cout << "此人信息:" << endl;
		PrintMessage(root);
		if (root->parent != NULL)
		{
			cout << "其父亲信息:" << endl;
			PrintMessage(root->parent);
		}
		treenode* p = root;
		int childrennum = 0;
		if (p->leftchild != NULL)
		{
			cout << "其孩子" << ++childrennum << "信息:" << endl;
			p = p->leftchild;
			PrintMessage(p);
			while (p->rightbrother != NULL)
			{
				cout << "其孩子" << ++childrennum << "信息:" << endl;
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

//按出生日期输出成员信息
void PrintMessageByBirthday(treenode* root)
{
	int year;
	int month;
	int day;
	cout << "请输入年" << endl;
	cin >> year;
	cin.ignore();
	cout << "请输入月" << endl;
	cin >> month;
	cin.ignore();
	cout << "请输入日" << endl;
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
		cout << "家谱中无此出生日期的人!" << endl;
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

//判断两人关系
void JudgeRalationship(treenode* root)
{
	string name1;
	string name2;
	cout << "请依次输入两个人的姓名" << endl;
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
		cout << "家谱中没有" << name1 << "这个人" << endl;
		return;
	}
	if (Person2 == NULL)
	{
		cout << "家谱中没有" << name2 << "这个人" << endl;
		return;
	}
	int depth1 = Person1->person.depth;
	int depth2 = Person2->person.depth;
	if (depth1 == depth2)
	{
		cout << name1 << "和" << name2 << "为兄弟关系" << endl;
		return;
	}
	if (depth1 - depth2 == -1)
	{
		if (Person2->parent == Person1)
		{
			cout << name1 << "是" << name2 << "的父亲" << endl;
			return;
		}
		else
		{
			cout<< name1 << "是" << name2 << "的叔叔" << endl;
		}
	}
	if (depth1 - depth2 == 1)
	{
		if (Person1->parent == Person2)
		{
			cout << name2 << "是" << name1 << "的父亲" << endl;
			return;
		}
		else
		{
			cout << name2 << "是" << name1 << "的叔叔" << endl;
			return;
		}
	}
	if (depth1 - depth2 == -2)
	{
		cout << name1 << "是" << name2 << "的爷爷" << endl;
		return;
		
	}
	if (depth1 - depth2 == 2)
	{
		cout << name2 << "是" << name1 << "的爷爷" << endl;
		return;

	}
	if (depth1 - depth2 < -2)
	{
		cout << name1 << "是" << name2 << "的祖先" << endl;
		return;

	}
	if (depth2 - depth1 < -2)
	{
		cout << name2 << "是" << name1 << "的祖先" << endl;
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
//添加孩子
void InsertChild(treenode*& root)
{
	string name;
	Date birthday;
	cout << "请输入要添加孩子成员的姓名" << endl;
	cin >> name;
	cin.ignore();
	cout << "请输入该成员的生日" << endl;
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
		cout << "输入信息有误!" << endl;
		return;
	}
	treenode* child = new treenode;
	child->depth = person->depth + 1;
	cout << "请输入姓名:" << endl;
	cin >> child->person.name;
	cin.ignore();
	cout << "请输入生日(年,月,日):" << endl;
	cin >> child->person.birthday.year;
	cin.ignore();
	cin >> child->person.birthday.month;
	cin.ignore();
	cin >> child->person.birthday.day;
	cin.ignore();
	cout << "请输入地址" << endl;
	cin >> child->person.address;
	child->person.depth = child->depth;
	int IsMarried;
	cout << "请输入婚姻状况,已婚输0，未婚输1" << endl;
	cin >> IsMarried;
	cin.ignore();
	int word = 1;
	while (word)
	{
		if (IsMarried == 0)
		{
			child->person.IsMarried = "已婚";
			word = 0;
		}
		else if (IsMarried == 1)
		{
			child->person.IsMarried = "未婚";
			word = 0;
		}
		else
		{
			cout << "输入数据非法,请重新输入" << endl;
			cin >> IsMarried;
		}
	}
	word = 1;
	cout << "该人是否在世，在世输0，已去世输1" << endl;
	int IsAlive;
	cin >> IsAlive;
	cin.ignore();
	while (word)
	{
		if (IsAlive == 0)
		{
			child->person.IsAlive = "在世";
			child->person.deathday.day = 0;
			child->person.deathday.month = 0;
			child->person.deathday.year = 0;
			word = 0;
		}
		else if (IsAlive == 1)
		{
			child->person.IsAlive = "离世";
			word = 0;
			cout << "请输入去世日期(年,月,日):" << endl;
			cin >> child->person.deathday.year;
			cin.ignore();
			cin >> child->person.deathday.month;
			cin.ignore();
			cin >> child->person.deathday.day;
			cin.ignore();
		}
		else
		{
			cout << "输入数据非法,请重新输入" << endl;
			cin >> IsAlive;
		}
		cout << "请输入备注" << endl;
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

//删除某成员
void DeleteMember(treenode*& root)
{
	string name;
	Date birthday;
	cout << "请输入该成员的姓名" << endl;
	cin >> name;
	cin.ignore();
	cout << "请输入该成员的生日" << endl;
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
		cout << "输入信息有误!" << endl;
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
		cout << "第一代人无法删除!" << endl;
	}
}

//修改某成员信息
void ModifyMember(treenode*& root)
{
	string name;
	Date birthday;
	cout << "请输入该成员的姓名" << endl;
	cin >> name;
	cin.ignore();
	cout << "请输入该成员的生日" << endl;
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
		cout << "输入信息有误!" << endl;
		return;
	}
	cout << "请按下列指引修改信息！" << endl;
	cout << "请输入姓名:" << endl;
	cin >> person->person.name;
	cin.ignore();
	cout << "请输入生日(年,月,日):" << endl;
	cin >> person->person.birthday.year;
	cin.ignore();
	cin >> person->person.birthday.month;
	cin.ignore();
	cin >> person->person.birthday.day;
	cin.ignore();
	cout << "请输入地址" << endl;
	cin >> person->person.address;
	person->person.depth = person->depth;
	int IsMarried;
	cout << "请输入婚姻状况,已婚输0，未婚输1" << endl;
	cin >> IsMarried;
	cin.ignore();
	int word = 1;
	while (word)
	{
		if (IsMarried == 0)
		{
			person->person.IsMarried = "已婚";
			word = 0;
		}
		else if (IsMarried == 1)
		{
			person->person.IsMarried = "未婚";
			word = 0;
		}
		else
		{
			cout << "输入数据非法,请重新输入" << endl;
			cin >> IsMarried;
		}
	}
	word = 1;
	cout << "该人是否在世，在世输0，已去世输1" << endl;
	int IsAlive;
	cin >> IsAlive;
	cin.ignore();
	cout << "请输入备注" << endl;
	cin >> person->person.remarks;
	cin.ignore();
	while (word)
	{
		if (IsAlive == 0)
		{
			person->person.IsAlive = "在世";
			person->person.deathday.day = 0;
			person->person.deathday.month = 0;
			person->person.deathday.year = 0;
			word = 0;
		}
		else if (IsAlive == 1)
		{
			person->person.IsAlive = "离世";
			word = 0;
			cout << "请输入去世日期(年,月,日):" << endl;
			cin >> person->person.deathday.year;
			cin.ignore();
			cin >> person->person.deathday.month;
			cin.ignore();
			cin >> person->person.deathday.day;
			cin.ignore();
		}
		else
		{
			cout << "输入数据非法,请重新输入" << endl;
			cin >> IsAlive;
		}
	}
	
}

//先序遍历把树中元素存在文件中
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
	cout << "----------------------------欢迎进入家谱管理系统--------------------------------" << endl;
	
	while (1)
	{
		cout << "--------------------------------菜单----------------------------------" << endl;
		cout << "1.查询第n代所有人的信息" << endl;
		cout << "2.按照姓名查询成员信息" << endl;
		cout << "3.按照出生日期查询成员信息" << endl;
		cout << "4.查询两人关系" << endl;
		cout << "5.为某成员添加孩子" << endl;
		cout << "6.删除某成员及其后代" << endl;
		cout << "7.修改某成员信息" << endl;
		cout << "8.输出所有成员信息" << endl;
		cout << "9.退出程序" << endl;
		int choice;
		cout << "请输入选择" << endl;
		cin >> choice;
		cin.ignore();
		switch (choice)
		{
			case 1:
			{
				cout << "请输入要查询的代数" << endl;
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
				cout << "输入数字非法，请重新输入!" << endl;
				break;
			}
		}
	}
	
}