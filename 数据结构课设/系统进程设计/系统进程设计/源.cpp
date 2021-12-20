/*
1、系统进程统计（必做）（链表）
[问题描述]
　　设计一个程序，每秒统计一次当前系统的进程状况，并按照内存使用自多到少排序打印输出相关信息。
  对已经结束的进程，另外给出一个列表，并显示该进程的结束时间和持续时间。
[基本要求]
（1） 该题目要求使用两个链式线性表。一个链表存储当前活动进程，要求使用单向链表，
并按照内存使用自多到少排序。另外一个链表存储已结束进程，要求使用双向链表，
按照持续时间自少到多排序。
（2） 每秒在窗口内更新一次当前系统进程情况，输出内容包括：进程名，持续时间，内存使用情况。
（3） 每秒在窗口内更新一次已结束进程情况，输出内容包括：进程名，持续时间，结束时间。
（4） 注意进程在这两个链表中的切换，一个进程既可被结束，也可以过一段时间后再被运行。
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
    string ProcessName;         //进程名
    int Duration;               //持续时间
    float Memory;               //内存使用情况
    int PID;                    //进程ID
    CurrentNode* next;    
    
}CurrentNode;

typedef struct EndNode
{
    string ProcessName;         //进程名
    int Duration;               //持续时间
    int EndTime;              //结束时间
    int PID;                    //进程ID
    EndNode* prior;             
    EndNode* succeeding;
}EndNode;

void PrintEndProcess(EndNode* head);

CurrentNode* CreateCurrentHead()        //当前进程的头
{
    CurrentNode* head = new CurrentNode;
    head->next = NULL;
    return head;
}

EndNode* CreateEndHead()                //结束进程的头
{
    EndNode* head = new EndNode;
    head->prior = NULL;
    head->succeeding = NULL;
    return head;
}

int PrintMemoryInfo(DWORD processID)       //获取某一进程的内存
{
    //API
    HANDLE hProcess;
    PROCESS_MEMORY_COUNTERS pmc;
    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
    if (hProcess == NULL)
        return 0;

    //GetProcessMemoryInfo()用于获取内存的使用情况
    if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))
    {
        CloseHandle(hProcess);

        //pmc.WorkingSetSize就是程序在当前代码处的内存使用量
        return pmc.WorkingSetSize;
    }
    return 0;
}

void CreateCurrentProcess(CurrentNode*& head)       //当前进程信息初始化到链表中
{
    CurrentNode* p = head;
    
    //
    PROCESSENTRY32 temp;
    temp.dwSize = sizeof(temp);

    //获取系统内的所有进程
    HANDLE hProcessSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    BOOL bMore = Process32First(hProcessSnapshot, &temp);
    while (bMore) 
    {
        CurrentNode* q = new CurrentNode;
        p->next = q;
        q->Duration = 0;
        q->PID = temp.th32ProcessID;
        q->Memory = PrintMemoryInfo(temp.th32ProcessID);
        _bstr_t name(temp.szExeFile);      //格式转换
        q->ProcessName = name;
        bMore = Process32Next(hProcessSnapshot, &temp);
        q->next = NULL;
        p = q;
    }
    //清除句柄
    CloseHandle(hProcessSnapshot);

}

bool IsCurrentExist(CurrentNode* Present, CurrentNode* Last)     //判断上一次某一进程是否在这次中
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

void UpdateCurrentProcess(CurrentNode*& Last , EndNode*& head)       //更新当前进程信息
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

bool IsEndExist(EndNode* Present, CurrentNode* Last)     //判断结束进程是否恢复
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

void UpdateEndProcess(EndNode*& head,CurrentNode* Current)      //更新结束进程
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

void CurrentBubbleSort(CurrentNode* head)        //单链表冒泡排序
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

void EndBubbleSort(EndNode*& head)      //双链表冒泡排序
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

void PrintCurrentProcess(CurrentNode* head)         //打印当前进程
{
    CurrentNode* p = head->next;
    cout.setf(ios::left);
    cout << setw(20) << "当前系统进程名" << '	' << "PID";
    cout.setf(ios::right, ios::left);
    cout << '	' << setw(17) << "内存使用情况" << '	' << "持续时间" << '	' << setw(20) << endl;
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

void PrintEndProcess(EndNode* head)     //打印结束进程
{
    cout.setf(ios::left);
    cout << setw(20) << "已结束进程名" << '	' << "PID";
    cout.setf(ios::right, ios::left);
    cout << '	' << setw(17) << "持续时间" << '	' << "结束时间" << '	' << setw(20) << endl;
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
