// @author: Folivora Li
// @copyright: Folivora Li


/*14、【2】公共钥匙盒（选做）（线性表，栈，队列）
[问题描述]
　　有一个学校的老师共用N个教室，按照规定，所有的钥匙都必须放在公共钥匙盒里，老师不能带钥匙回家。每次老师上课前，都从公共钥匙盒里找到自己上课的教室的钥匙去开门，上完课后，再将钥匙放回到钥匙盒中。
　　钥匙盒一共有N个挂钩，从左到右排成一排，用来挂N个教室的钥匙。一串钥匙没有固定的悬挂位置，但钥匙上有标识，所以老师们不会弄混钥匙。
　　每次取钥匙的时候，老师们都会找到自己所需要的钥匙将其取走，而不会移动其他钥匙。每次还钥匙的时候，还钥匙的老师会找到最左边的空的挂钩，将钥匙挂在这个挂钩上。如果有多位老师还钥匙，则他们按钥匙编号从小到大的顺序还。如果同一时刻既有老师还钥匙又有老师取钥匙，则老师们会先将钥匙全还回去再取出。
　　今天开始的时候钥匙是按编号从小到大的顺序放在钥匙盒里的。有K位老师要上课，
  给出每位老师所需要的钥匙、开始上课的时间和上课的时长，假设下课时间就是还钥匙时间，
  请问最终钥匙盒里面钥匙的顺序是怎样的？
[基本要求]
输入格式
　　输入的第一行包含两个整数N, K。
　　接下来K行，每行三个整数w, s, c，分别表示一位老师要使用的钥匙编号、开始上课的时间和上课的时长。
  可能有多位老师使用同一把钥匙，但是老师使用钥匙的时间不会重叠。
　　保证输入数据满足输入格式，你不用检查数据合法性。
输出格式
　　输出一行，包含N个整数，相邻整数间用一个空格分隔，依次表示每个挂钩上挂的钥匙编号。
样例输入
5 2
4 3 3
2 2 7
样例输出
1 4 3 2 5
样例说明
　　第一位老师从时刻3开始使用4号教室的钥匙，使用3单位时间，所以在时刻6还钥匙。第二位老师从时刻2开始使用钥匙，
  使用7单位时间，所以在时刻9还钥匙。
　　每个关键时刻后的钥匙状态如下（X表示空）：
　　时刻2后为1X345；
　　时刻3后为1X3X5；
　　时刻6后为143X5；
　　时刻9后为14325。
课程设计要求：
（1）要求从文本文件中输入；
（2）根据时间进程，将取走钥匙和归还钥匙分别视为事件，放入队列中，然后通过每个事件的先后发生对钥匙盒的状态
进行变更；
（3）严格按照要求的输入输出格式进行数据的输入、输出（训练CSP考试中的格式化输入输出的正确性）；
（4）选做：通过图形界面来显示钥匙盒的即时状态，以及事件队列的状态。*/

//首先我不是很明白，为什么唯独这个题要求从文本文件输入？？？
#include<iostream>
using namespace std;
typedef struct {
    int key;
    int state;
    int time;
}KeyNode;

typedef struct QueueNode{
    QueueNode* next;
    KeyNode data;
}QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
}LinkQueue;

void InitQueue(LinkQueue& q)
{
    q.front = q.rear = new QueueNode;
    q.front->next = NULL;
    q.front->data.key = -1;
    q.front->data.state = -1;
    q.front->data.time = -1;
}
void Insert(LinkQueue& q, KeyNode data)
{

    QueueNode* p = q.front;
    QueueNode* pre = p;
    QueueNode* p1 = new QueueNode;
    p1->data = data;
    while (p != NULL)
    {
        if (p->data.time < data.time)
        {
            pre = p;
            p = p->next;
        }
        else if (p->data.time == data.time)
        {
            if (data.state > p->data.state)
            {
                p1->next = p;
                pre->next = p1;
                return;
            }
            else if (data.state < p->data.state)
            {
                pre = p;
                p = p->next;
            }
            else
            {
                if (data.key < p->data.key)
                {
                    p1->next = p;
                    pre->next = p1;
                    return;
                }
                else
                {
                    pre = p;
                    p = p->next;
                }
            }
        }
        else
        {
            p1->next = p;
            pre->next = p1;
            return;

        }
    }
    pre->next = p1;
    p1->next = NULL;
    return;
}
int main()
{
    int N;
    int K;
    cin >> N;
    cin.ignore();
    cin >> K;
    cin.ignore();
    int key;
    int starttime;
    int lasttime;
    LinkQueue q;
    InitQueue(q);

    KeyNode* Box = new KeyNode[2 * K];
    for (int i = 0; i < K; i++)
    {
        cin >> key;
        cin.ignore();
        cin >> starttime;
        cin.ignore();
        cin >> lasttime;
        cin.ignore();
        Box[i].key = key;
        Box[i].state = 0;
        Box[i].time = starttime;
        Box[2 * K - i - 1].key = key;
        Box[2 * K - i - 1].state = 1;
        Box[2 * K - i - 1].time = lasttime + starttime;

    }
    int* Key = new int[N];
    for (int i = 0; i < N; i++)
    {
        Key[i] = i + 1;
    }
    for (int i = 0; i < 2 * K; i++)
    {
        Insert(q, Box[i]);
    }
    QueueNode* p = q.front->next;
    while (p != NULL)
    {
        if (p->data.state == 0)         //取出钥匙
        {
            for (int i = 0; i < N; i++)
            {
                if (Key[i] == p->data.key)
                {
                    Key[i] = 0;
                    break;
                }
            }   
        }
        else
        {
            for (int i = 0; i < N; i++)
            {
                if (Key[i] == 0)
                {
                    Key[i] = p->data.key;
                    break;
                }
            }
        }
        p = p->next;
    }
    for (int i = 0; i < N; i++)
    {
        cout << Key[i] << "  ";
    }
    cout << endl;
}