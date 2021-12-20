#define _CRT_SECURE_NO_WARNINGS
/*
8�������㷨�Ƚ� ��������������
[��������]
���������������10��������ÿ��������50000�������������ʹ��һ�����������򣬵ڶ������������򣩣�
����ֱ�Ӳ�������ϣ������ð�����򡢿�������ѡ�����򡢶����򣬹鲢���򡢻�������
8�����򷽷��������򣨽��Ϊ��С�����˳�򣩣���ͳ��ÿһ�������㷨�Բ�ͬ�������ķѵ�ʱ�䡣
 [����Ҫ��]
��1�� ԭʼ���ݴ����ļ��У�����ͬ�����Բ�ͬ�㷨���в��ԣ�
��2�� ��Ļ��ʾÿ�������㷨�Բ�ͬ����������ʱ�䣻
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string>
#include <Windows.h>
#include <fstream>

using namespace std;
typedef struct LinkNode {
    int data;
    LinkNode* next;
}LinkNode;
//��������
void Insert_Sort(vector<int>& a)
{
    int temp;
    int j;
    for (int i = 1; i < a.size(); i++)
    {
        temp = a[i];
        for (j = i - 1 ; j >= 0; j--)
        {
            if (temp < a[j])
            {
                a[j + 1] = a[j];
            }
            else
            {
                break;
            }
        }
        //cout << i << " ";
        a[j + 1] = temp;
    }
}
//ϣ������
void Shell_Sort(vector<int>& a)
{
    //����Sedgewick��������
    int Sedgewick[12] = { 1,5,19,41,109,209,505,929,2161,3905,8929,16001 };
    int length = 12;
    for (int i = length - 1; i >= 0; i--)
    {
        if (Sedgewick[i] > a.size())
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
        for (int j = deita; j < a.size(); j = j + deita)
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
            //cout << j << "  ";
        }
        //cout << i << "  ";
    }

}
//��������
void Radix_Sort(vector<int>& a)
{
    vector<int>::iterator iter;
    iter = a.begin();
    int max = *max_element(iter,iter + a.size());
    int digit = 0;
    int maxcopy = max;
    while (maxcopy != 0)
    {
        maxcopy = maxcopy / 10;
        digit++;
    }
    LinkNode* t[10];
    LinkNode* start[10];
    for (int i = 0; i < 10; i++)
    {
        t[i] = new LinkNode;
        t[i]->next = NULL;
        start[i] = t[i];
    }
    int mod = 1;
    for (int count = 0; count < digit; count++)
    {
        for (int i = 0; i < a.size(); i++)
        {
            LinkNode* p = new LinkNode;
            t[(a[i] / mod) % 10]->next = p;
            p->data = a[i];
            p->next = NULL;
            t[(a[i] / mod) % 10] = p;
        }
        for (int i = 0; i < 10; i++)
        {
            t[i] = start[i];
        }
        mod = mod * 10;
        int j = 0;
        for (int i = 0; i < 10; i++)
        {
            LinkNode* q = t[i]->next;
            LinkNode* q1 = t[i];
            while (q != NULL)
            {
                q1 = q;
                a[j++] = q->data;
                q = q->next;
                delete q1;
            }
            t[i]->next = NULL;
        }
        j = 0;
    }
    
}

void Bubble_Sort(vector<int>& a)
{
    int temp;
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < a.size() - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;

            }
        }
       // cout << i << endl;
    }
}
//ѡ������
void Choice_Sort(vector<int>& a)
{
    int min = a[0];
    int serial_min = 0;
    int temp;
    int serial = 0;
    int word = 0;
    while (serial < a.size())
    {
        for (int i = serial; i < a.size(); i++)
        {
            if (word == 0)
            {
                min = a[i];
                serial_min = i;
                word = 1;
            }

            if (min > a[i])
            {
                min = a[i];
                serial_min = i;
            }
        }
        temp = a[serial_min];
        a[serial_min] = a[serial];
        a[serial] = temp;
        serial++;
        word = 0;
        //cout << serial << " ";

    }


}


//�鲢����
int Min(int a1, int a2, int& serial1, int& serial2)
{
    if (a1 < a2)
    {
        serial1++;
        return a1;
    }
    serial2++;
    return a2;
}
void MainMerge(int* a, int l, int mid, int r)
{
    int serial = l;
    int serial1 = l;

    int serial2 = mid + 1;
    int* b = new int[r - l + 1];
    for (int i = l; i <= r; i++)
    {
        b[i - l] = a[i];
    }
    while ((serial1 <= mid) && (serial2 <= r))
    {
        a[serial++] = Min(b[serial1 - l], b[serial2 - l], serial1, serial2);
    }
    while (serial2 <= r)
    {
        a[serial++] = b[serial2 - l];
        serial2++;
    }
    while (serial1 <= mid)
    {
        a[serial++] = b[serial1 - l];
        serial1++;
    }
}
void Merge_Sort(int* a, int l, int r)
{
    if (l >= r)
    {
        return;
    }
    int mid;
    mid = (l + r) / 2;
    Merge_Sort(a, l, mid);
    Merge_Sort(a, mid + 1, r);
    MainMerge(a, l, mid, r);
}

//��������
void Swap(int& a, int& b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}
void QuickSort(int* a, int left, int right)
{
    //ȡ��Ԫ

    int l = left - 1;
    int r = right - 2;
    if (r - l >= 0)
    {
        int center = (left + right) / 2;
        if (a[left] > a[right])
        {
            Swap(a[left], a[right]);
            
        }
        if (a[left] > a[center])
        {
            Swap(a[left], a[center]);
        }
        if (a[center] > a[right])
        {
            Swap(a[center], a[right]);
        }
        int pivot = a[center];
        Swap(a[center], a[right - 1]);
        
        while (1)
        {
            while (a[++l] <= pivot)
            {
                
            }
            while (a[--r] >= pivot)
            {
               
            }
            if (l < r)
            {
                Swap(a[l], a[r]);
            }
            else
            {
                break;
            }
            
        }
        Swap(a[l], a[right - 1]);
        QuickSort(a, left, l - 1);
        QuickSort(a, l + 1, right);
    }
    else
    {
        if (right - left == 2)
        {
            
            if (a[left] > a[left + 1])
            {
                Swap(a[left], a[left + 1]);
            }
            if (a[left] > a[right])
            {
                Swap(a[left], a[right]);

            }
            if (a[left + 1] > a[right])
            {
                Swap(a[left + 1], a[right]);

            }
        }
        if (right - left == 1)
        {
            if (a[left] > a[right])
            {
                Swap(a[left], a[right]);

            }
        }
    }
}

//������
void Build(int i, int* a, int maxdepth, int n)
{

    int depth;
    depth = log(i + 1) / log(2);
    if (depth + 1 == maxdepth)
    {
        if ((2 * i + 1) < n)
        {
            if (a[i] < a[2 * i + 1])
            {
                Swap(a[i], a[2 * i + 1]);
            }
        }
        if ((2 * i + 2) < n)
        {
            if (a[i] < a[2 * i + 2])
            {
                Swap(a[i], a[2 * i + 2]);
            }
        }

    }
    else if (depth + 1 < maxdepth)
    {

        if (a[i] < a[2 * i + 1] && (2 * i + 1 < n))
        {
            Swap(a[i], a[2 * i + 1]);
        }
        if ((a[i] < a[2 * i + 2]) && (2 * i + 2 < n))
        {
            Swap(a[i], a[2 * i + 2]);
        }
        Build(2 * i + 1, a, maxdepth, n);
        Build(2 * i + 2, a, maxdepth, n);
    }

}
void BuildMaxHeap(int* a, int n)
{
    int serial = n / 2;
    int maxdepth = log(n) / log(2);
    for (int i = serial - 1; i >= 0; i--)
    {
        Build(i, a, maxdepth, n);
    }
}
void Heap_Sort(int* a, int n)
{
    BuildMaxHeap(a, n);
    for (int i = n - 1; i > 0; i--)
    {
        Swap(a[0], a[i]);
        Build(0, a, log(n) / log(2), i);
        //cout << i << "  ";
    }
}
int main()
{
    int* N = new int[50000];
    string name = "rand";
    DWORD time_start;
    DWORD time_end;
    string truename = name;
    char* a=new char;
    fstream file;
    vector<int> vec1;
    vector<int> vec2;
    int num;
    for (int K = 9; K >= 0; K--)
    {
        truename = truename + _itoa(i,a,10);
        cout << "�ļ���:" << truename << endl;
        file.open("D:\\" + truename + ".txt", ios::in);
        if (file.fail())
        {
            cout << "error!";
            exit(1);
        }
        file >> num;
        vec1.push_back(num);
        while (!file.eof())
        {
            vec1.push_back(num);
            file >> num;
        }
        for (int i = 0; i < 50000; i++)
        {
            N[i] = vec1[i];
        }
        vec2 = vec1;
        file.close();
         time_start = GetTickCount();
       Insert_Sort(vec1);
       time_end = GetTickCount();
       cout << "����������ʱ" << time_end - time_start << "����" << endl;
       vec1 = vec2;
       time_start = GetTickCount();
       Shell_Sort(vec1);
       time_end = GetTickCount();
       cout << "ϣ��������ʱ" << time_end - time_start << "����" << endl;
       vec1 = vec2;
       time_start = GetTickCount();
       Radix_Sort(vec1);
       time_end = GetTickCount();
       cout << "����������ʱ" << time_end - time_start << "����" << endl;
       
       vec1 = vec2;
       time_start = GetTickCount();
       Bubble_Sort(vec1);
       time_end = GetTickCount();
       
       cout << "ð��������ʱ" << time_end - time_start << "����" << endl;
       vec1 = vec2;
       time_start = GetTickCount();
       Choice_Sort(vec1);
       time_end = GetTickCount();
       cout << "ѡ��������ʱ" << time_end - time_start << "����" << endl;
       time_start = GetTickCount();
        Merge_Sort(N,0,49999);
        time_end = GetTickCount();
        cout << "�鲢������ʱ" << time_end - time_start << "����" << endl;
        time_start = GetTickCount();
        Sleep(1000);
        QuickSort(N, 0, 49999);
        time_end = GetTickCount();
        cout << "����������ʱ" << time_end - time_start << "����" << endl;
        
        for (int i = 0; i < 50000; i++)
        {
            N[i] = vec2[i];
        }
        time_start = GetTickCount();
        Heap_Sort(N, 50000);
        time_end = GetTickCount();
        cout << "��������ʱ" << time_end - time_start << "����" << endl;
        cout << endl;
        cout << endl;
        vec1.clear();
        vec2.clear();
        file.close();
        truename = name;
        
    }
}