// @author: Folivora Li
// @copyright: Folivora Li

/*11、【1】 魔法优惠券（选做）（排序）
[问题描述]
在火星上有个魔法商店，通过魔法优惠券。每个优惠券上印有一个整数面值K，
表示若你在购买某商品使用这张优惠券，可以得到K倍该商品价值的回报。
该商店还免费赠送一些有价值的商品，但如果你在领取免费赠品的时候使用面值为正的优惠券，
则必须倒贴给商品K倍该商品价值的金额……但是不要紧，还有面值为负的优惠券可以用。
例如，给定一组优惠券，面值分别为1、2、4、-1；对应一组商品，价值为火星币7、6、-2、-3，
其中负的价值表示该商品是免费赠品。我们可以将优惠券3（面值4）用在商品1（价值7）上，
得到火星币28的回报。优惠券4（面值-1）用在商品4（价值-3）上，得到火星币3的回报。
但是，如果一不小心把优惠券3（面值4）用到商品4（价值-3）上，你必须倒贴给商店火星币12个。
同样，把优惠券4（面值-1）用到商品1（价值7）上，你必须倒贴给商店火星币7个。
规定每张优惠券和每件商品都只能最多被使用一次，求你可以得到的最大回报。 
[基本要求]
（1）输入说明：输入有两行。第一行首先给出优惠券的个数N，随后给出N个优惠券的整数面值。 
第二行首先给出商品的个数M，随后给出M个商品的整数价值。N和M在[1,106]之间，所有的数据大小不超过230
，数字间以空格分隔。 
（2）输出说明：输出可以得到的最大回报。
（3）测试用例： 
4 1 2 4 -1
      4 7 6 -2 -3
  43

输入：4 3 2 6 1 
      3 2 6 3
输出：49

输入： 7 3 36 -1 73 2 3 6
       6 -1 -1 -1 -1 -1 -1
输出： 1*/


#include <iostream>
#include <algorithm>
using namespace std;
int Min(int a, int b)
{
    if (a > b)
    {
        return b;

    }
    else
    {
        return a;
    }
}
int main()
{
    int N;
    cin >> N;
    cin.ignore();
    int* a = new int[N];
    int positive1 = 0;
    int positive2 = 0;
    int negative1 = 0;
    int negative2 = 0;
    for (int i = 0; i < N; i++)
    {
        cin >> a[i];
        cin.ignore();
        if (a[i] > 0)
        {
            positive1++;
        }
    }
    negative1 = N - positive1;
    int M;
    cin >> M;
    cin.ignore();
    int* b = new int[M];
    for (int i = 0; i < M; i++)
    {
        cin >> b[i];
        cin.ignore();
        if (b[i] > 0)
        {
            positive2++;
        }

    }
    negative2 = N - positive2;
    sort(a, a + N, greater<int>());
    sort(b, b + M, greater<int>());
    int min = Min(positive1, positive2);
    int total = 0;
    for (int i = 0; i < min; i++)
    {
        total = total + a[i] * b[i];
    }
    min = Min(negative1, negative2);
    reverse(a, a + N);
    reverse(b, b + M);
    for (int i = 0; i < min; i++)
    {
        total = total + a[i] * b[i];
    }
    cout << total << endl;
}