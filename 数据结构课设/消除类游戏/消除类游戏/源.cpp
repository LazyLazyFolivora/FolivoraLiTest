// @author: Folivora Li
// @copyright: Folivora Li

#include <iostream>
#include <string>
using namespace std;
int main()
{
    int m, n;
    // cout << "请输入行和列数" << endl;
    cin >> n;
    cin.ignore();
    cin >> m;
    cin.ignore();
    int** chess = new int* [n];
    for (int i = 0; i < n; i++)
    {
        chess[i] = new int[m];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> chess[i][j];
            cin.ignore();
        }
    }
    int** chess1 = new int* [n];
    for (int i = 0; i < n; i++)
    {
        chess1[i] = new int[m];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            chess1[i][j] = 0;
        }
    }
    int num;
    int i1, j1;
    int count1 = 0;
    int count2 = 0;
    int i2, j2;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            count1 = 0;
            i1 = i;
            j1 = j;
            num = chess[i1][j1];
            while ((chess[i1][j1] == num) && (i1 < n))
            {
                count1++;
                i1++;
                if (i1 == n)
                {
                    break;
                }
            }
            if (count1 >= 3)
            {

                for (i2 = i; i2 < i1; i2++)
                {
                    chess1[i2][j] = 1;
                }
            }



        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            count2 = 0;
            i1 = i;
            j1 = j;
            num = chess[i1][j1];

            while ((chess[i1][j1] == num) && (j1 < m))
            {
                count2++;
                j1++;
                if (j1 == m)
                {
                    break;
                }
            }
            if (count2 >= 3)
            {

                for (j2 = j; j2 < j1; j2++)
                {
                    chess1[i][j2] = 1;
                }
            }


        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (chess1[i][j] == 1)
            {
                chess[i][j] = 0;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << chess[i][j] << " ";
        }
        cout << endl;
    }

}