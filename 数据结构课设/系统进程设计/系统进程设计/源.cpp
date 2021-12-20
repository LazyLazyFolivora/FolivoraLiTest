/*
1��ϵͳ����ͳ�ƣ�������������
[��������]
�������һ������ÿ��ͳ��һ�ε�ǰϵͳ�Ľ���״�����������ڴ�ʹ���Զൽ�������ӡ��������Ϣ��
  ���Ѿ������Ľ��̣��������һ���б�����ʾ�ý��̵Ľ���ʱ��ͳ���ʱ�䡣
[����Ҫ��]
��1�� ����ĿҪ��ʹ��������ʽ���Ա�һ������洢��ǰ����̣�Ҫ��ʹ�õ�������
�������ڴ�ʹ���Զൽ����������һ������洢�ѽ������̣�Ҫ��ʹ��˫������
���ճ���ʱ�����ٵ�������
��2�� ÿ���ڴ����ڸ���һ�ε�ǰϵͳ���������������ݰ�����������������ʱ�䣬�ڴ�ʹ�������
��3�� ÿ���ڴ����ڸ���һ���ѽ������������������ݰ�����������������ʱ�䣬����ʱ�䡣
��4�� ע������������������е��л���һ�����̼ȿɱ�������Ҳ���Թ�һ��ʱ����ٱ����С�
*/
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<windows.h>
#include<TLHELP32.h>
#include<iomanip>
#include<string>
#include"Psapi.h"
#include<ctime>
#include <comdef.h>
#pragma comment(lib,"Psapi.lib")
using namespace std;

typedef struct CurrentNode {
    string ProcessName;         //������
    int Duration;               //����ʱ��
    float Memory;               //�ڴ�ʹ�����
    int PID;                    //����ID
    CurrentNode* next;    
    
}CurrentNode;

typedef struct EndNode
{
    string ProcessName;         //������
    int Duration;               //����ʱ��
    int EndTime;              //����ʱ��
    int PID;                    //����ID
    EndNode* prior;             
    EndNode* succeeding;
}EndNode;

void PrintEndProcess(EndNode* head);

CurrentNode* CreateCurrentHead()        //��ǰ���̵�ͷ
{
    CurrentNode* head = new CurrentNode;
    head->next = NULL;
    return head;
}

EndNode* CreateEndHead()                //�������̵�ͷ
{
    EndNode* head = new EndNode;
    head->prior = NULL;
    head->succeeding = NULL;
    return head;
}

int PrintMemoryInfo(DWORD processID)       //��ȡĳһ���̵��ڴ�
{
    //API
    HANDLE hProcess;
    PROCESS_MEMORY_COUNTERS pmc;
    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
    if (hProcess == NULL)
        return 0;

    //GetProcessMemoryInfo()���ڻ�ȡ�ڴ��ʹ�����
    if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))
    {
        CloseHandle(hProcess);

        //pmc.WorkingSetSize���ǳ����ڵ�ǰ���봦���ڴ�ʹ����
        return pmc.WorkingSetSize;
    }
    return 0;
}

void CreateCurrentProcess(CurrentNode*& head)       //��ǰ������Ϣ��ʼ����������
{
    CurrentNode* p = head;
    
    //
    PROCESSENTRY32 temp;
    temp.dwSize = sizeof(temp);

    //��ȡϵͳ�ڵ����н���
    HANDLE hProcessSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    BOOL bMore = Process32First(hProcessSnapshot, &temp);
    while (bMore) 
    {
        CurrentNode* q = new CurrentNode;
        p->next = q;
        q->Duration = 0;
        q->PID = temp.th32ProcessID;
        q->Memory = PrintMemoryInfo(temp.th32ProcessID);
        _bstr_t name(temp.szExeFile);      //��ʽת��
        q->ProcessName = name;
        bMore = Process32Next(hProcessSnapshot, &temp);
        q->next = NULL;
        p = q;
    }
    //������
    CloseHandle(hProcessSnapshot);

}

bool IsCurrentExist(CurrentNode* Present, CurrentNode* Last)     //�ж���һ��ĳһ�����Ƿ��������
{
    CurrentNode* p = Present->next;
    while (p != NULL)
    {
        if (Last->PID == p->PID)
        {
            p->Duration = Last->Duration;
            p->Duration++;
            return true;
        }
        p = p->next;
    }
    return false;
}

void UpdateCurrentProcess(CurrentNode*& Last , EndNode*& head)       //���µ�ǰ������Ϣ
{
    CurrentNode* Present = CreateCurrentHead();
    CreateCurrentProcess(Present);
    CurrentNode* p = Last->next;
    EndNode* h = head;
    while (p->next != NULL)
    {
        if (!IsCurrentExist(Present, p))
        {
            while (h->succeeding != NULL)
            {
                h = h->succeeding;
            }
            
            EndNode* h1 = new EndNode;
            h1->EndTime = p->Duration;
            h1->ProcessName = p->ProcessName;
            h1->PID = p->PID;
            h1->Duration = 0;
            h1->prior = h;
            h->succeeding = h1;
            h1->succeeding = NULL;
            h = h1;
        }
        p = p->next;
    }
    p = Last;
    CurrentNode* p1 = p;
    delete p1;
    Last = Present;

}

bool IsEndExist(EndNode* Present, CurrentNode* Last)     //�жϽ��������Ƿ�ָ�
{
    CurrentNode* p = Last->next;
    while (p != NULL)
    {
        if ((Present->PID == p->PID)&&(Present->ProcessName == p->ProcessName))
        {
            return true;
        }
        p = p->next;
    }
    return false;
}

void UpdateEndProcess(EndNode*& head,CurrentNode* Current)      //���½�������
{
    EndNode* p = head;
    EndNode* p1 = head;
    p1 = p1->succeeding;
    while (p1 != NULL)
    {
        if (IsEndExist(p1, Current))
        {
            if (p1->succeeding != NULL)
            {
                p->succeeding = p1->succeeding;
                p1->succeeding->prior = p;
                p1->succeeding = NULL;
                p1->prior = NULL;
                EndNode* p2 = p1;
                p1 = p->succeeding;
                delete p2;
                continue;
            }
            else
            {
                p->succeeding = NULL;
                p1->prior = NULL;
                EndNode* p2 = p1;
                delete p2;
                p1 = NULL;
                break;
            }
            
        }
        else
        {
            p1->Duration++;
        }
        p = p1;
        p1 = p1->succeeding;
    }
    
}

void SwapCurrent(CurrentNode*& p1,CurrentNode*& p2)
{
    float temp;
    temp = p1->Duration;
    p1->Duration = p2->Duration;
    p2->Duration = temp;

    temp = p1->Memory;
    p1->Memory = p2->Memory;
    p2->Memory = temp;

    string name;
    name = p1->ProcessName;
    p1->ProcessName = p2->ProcessName;
    p2->ProcessName = name;

    temp = p1->PID;
    p1->PID = p2->PID;
    p2->PID = temp;
    
}

void SwapEnd(EndNode*& p1, EndNode*& p2)
{
    float temp;
    temp = p1->Duration;
    p1->Duration = p2->Duration;
    p2->Duration = temp;

    temp = p1->EndTime;
    p1->EndTime = p2->EndTime;
    p2->EndTime = temp;

    string name;
    name = p1->ProcessName;
    p1->ProcessName = p2->ProcessName;
    p2->ProcessName = name;

    temp = p1->PID;
    p1->PID = p2->PID;
    p2->PID = temp;

}

void CurrentBubbleSort(CurrentNode* head)        //������ð������
{
    CurrentNode* p1 = head->next;
    if (p1 == NULL)
    {
        return;
    }
    CurrentNode* p2 = p1->next;
    if (p2 == NULL)
    {
        return;
    }
    CurrentNode* p3 = NULL;
    while (1)
    {
        if (p2 == p3)
        {
            p3 = p1;
            p1 = head->next;
            p2 = p1->next;
        }
        if (p1->Memory < p2->Memory)
        {
            SwapCurrent(p1, p2);
        }
        if (p2 == p3)
        {
            break;
        }
        p1 = p1->next;
        p2 = p2->next;
    }

}

void EndBubbleSort(EndNode*& head)      //˫����ð������
{

    EndNode* p1 = head->succeeding;
    if (p1 == NULL)
    {
        return;
    }
    EndNode* p2 = p1->succeeding;
    if (p2 == NULL)
    {
        return;
    }
    EndNode* p3 = NULL;
    while (1)
    {
        if (p2 == p3)
        {
            p3 = p1;
            p1 = head->succeeding;
            p2 = p1->succeeding;
        }
        if (p1->Duration > p2->Duration)
        {
            SwapEnd(p1, p2);
        }
        if (p2 == p3)
        {
            break;
        }
        p1 = p1->succeeding;
        p2 = p2->succeeding;
    }
}

void PrintCurrentProcess(CurrentNode* head)         //��ӡ��ǰ����
{
    CurrentNode* p = head->next;
    cout.setf(ios::left);
    cout << setw(20) << "��ǰϵͳ������" << '	' << "PID";
    cout.setf(ios::right, ios::left);
    cout << '	' << setw(17) << "�ڴ�ʹ�����" << '	' << "����ʱ��" << '	' << setw(20) << endl;
    cout << "----------------------------------------------------------------" << endl;
    while (p != NULL)
    {
        cout << p->ProcessName;
        cout.setf(ios::left);
        cout << '	' << p->PID;

        cout.setf(ios::right, ios::left);
        if (p->Memory < 1024)
        {
            cout << '	' << setw(15) << p->Memory << "B";
        }
        else
        {
            cout << '	' << setw(15) << p->Memory / 1024.0 << "KB";
        }
        
        if (p->Duration < 60)
        {
            cout << '	' << p->Duration << "s" << endl;
        }
            
        if (p->Duration >= 60)
        {
            cout << '	' << p->Duration / 60 << "m  " << p->Duration % 60 << "s" << endl;
        }
            

        p = p->next;
    }
}

void PrintEndProcess(EndNode* head)     //��ӡ��������
{
    cout.setf(ios::left);
    cout << setw(20) << "�ѽ���������" << '	' << "PID";
    cout.setf(ios::right, ios::left);
    cout << '	' << setw(17) << "����ʱ��" << '	' << "����ʱ��" << '	' << setw(20) << endl;
    cout << "----------------------------------------------------------------" << endl;
    EndNode* p = head->succeeding;
    while (p != NULL)
    {
        cout << p->ProcessName;
        cout.setf(ios::left);
        cout << '\t' << p->PID;

        cout.setf(ios::right, ios::left);
        if (p->Duration < 60)
            cout << '	' << setw(15) << p->Duration << "s";
        if (p->Duration >= 60)
            cout << '	' << setw(12) << p->Duration / 60 << "m  " << p->Duration % 60 << "s";


        cout.setf(ios::left, ios::right);

        if (p->EndTime < 60)
            cout << '	' << p->EndTime << "s" << endl;
        if (p->EndTime >= 60)
            cout << '	' << p->EndTime / 60 << "m  " << p->EndTime % 60 << "s" << endl;
        p = p->succeeding;
    }
}

int main()
{
    CurrentNode* L = CreateCurrentHead();
    EndNode* E = CreateEndHead();
    CreateCurrentProcess(L);
    while (1)
    {
        CurrentBubbleSort(L);
        EndBubbleSort(E);
        PrintCurrentProcess(L);
        PrintEndProcess(E);
        UpdateCurrentProcess(L, E);
        UpdateEndProcess(E, L);
        Sleep(1000);
        system("cls");
    }
}
