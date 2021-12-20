// @author: Folivora Li
// @copyright: Folivora Li


/*14����2������Կ�׺У�ѡ���������Ա�ջ�����У�
[��������]
������һ��ѧУ����ʦ����N�����ң����չ涨�����е�Կ�׶�������ڹ���Կ�׺����ʦ���ܴ�Կ�׻ؼҡ�ÿ����ʦ�Ͽ�ǰ�����ӹ���Կ�׺����ҵ��Լ��ϿεĽ��ҵ�Կ��ȥ���ţ�����κ��ٽ�Կ�׷Żص�Կ�׺��С�
����Կ�׺�һ����N���ҹ����������ų�һ�ţ�������N�����ҵ�Կ�ס�һ��Կ��û�й̶�������λ�ã���Կ�����б�ʶ��������ʦ�ǲ���Ū��Կ�ס�
����ÿ��ȡԿ�׵�ʱ����ʦ�Ƕ����ҵ��Լ�����Ҫ��Կ�׽���ȡ�ߣ��������ƶ�����Կ�ס�ÿ�λ�Կ�׵�ʱ�򣬻�Կ�׵���ʦ���ҵ�����ߵĿյĹҹ�����Կ�׹�������ҹ��ϡ�����ж�λ��ʦ��Կ�ף������ǰ�Կ�ױ�Ŵ�С�����˳�򻹡����ͬһʱ�̼�����ʦ��Կ��������ʦȡԿ�ף�����ʦ�ǻ��Ƚ�Կ��ȫ����ȥ��ȡ����
�������쿪ʼ��ʱ��Կ���ǰ���Ŵ�С�����˳�����Կ�׺���ġ���Kλ��ʦҪ�ϿΣ�
  ����ÿλ��ʦ����Ҫ��Կ�ס���ʼ�Ͽε�ʱ����Ͽε�ʱ���������¿�ʱ����ǻ�Կ��ʱ�䣬
  ��������Կ�׺�����Կ�׵�˳���������ģ�
[����Ҫ��]
�����ʽ
��������ĵ�һ�а�����������N, K��
����������K�У�ÿ����������w, s, c���ֱ��ʾһλ��ʦҪʹ�õ�Կ�ױ�š���ʼ�Ͽε�ʱ����Ͽε�ʱ����
  �����ж�λ��ʦʹ��ͬһ��Կ�ף�������ʦʹ��Կ�׵�ʱ�䲻���ص���
������֤�����������������ʽ���㲻�ü�����ݺϷ��ԡ�
�����ʽ
�������һ�У�����N��������������������һ���ո�ָ������α�ʾÿ���ҹ��Ϲҵ�Կ�ױ�š�
��������
5 2
4 3 3
2 2 7
�������
1 4 3 2 5
����˵��
������һλ��ʦ��ʱ��3��ʼʹ��4�Ž��ҵ�Կ�ף�ʹ��3��λʱ�䣬������ʱ��6��Կ�ס��ڶ�λ��ʦ��ʱ��2��ʼʹ��Կ�ף�
  ʹ��7��λʱ�䣬������ʱ��9��Կ�ס�
����ÿ���ؼ�ʱ�̺��Կ��״̬���£�X��ʾ�գ���
����ʱ��2��Ϊ1X345��
����ʱ��3��Ϊ1X3X5��
����ʱ��6��Ϊ143X5��
����ʱ��9��Ϊ14325��
�γ����Ҫ��
��1��Ҫ����ı��ļ������룻
��2������ʱ����̣���ȡ��Կ�׺͹黹Կ�׷ֱ���Ϊ�¼�����������У�Ȼ��ͨ��ÿ���¼����Ⱥ�����Կ�׺е�״̬
���б����
��3���ϸ���Ҫ������������ʽ�������ݵ����롢�����ѵ��CSP�����еĸ�ʽ�������������ȷ�ԣ���
��4��ѡ����ͨ��ͼ�ν�������ʾԿ�׺еļ�ʱ״̬���Լ��¼����е�״̬��*/

//�����Ҳ��Ǻ����ף�ΪʲôΨ�������Ҫ����ı��ļ����룿����
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
        if (p->data.state == 0)         //ȡ��Կ��
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