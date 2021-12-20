// @author: Folivora Li
// @copyright: Folivora Li

#define _CRT_SECURE_NO_WARNINGS
/*
15、【3】URL映射（选做）（字符串）
问题描述 
　　URL 映射是诸如 Django、Ruby on Rails 等网页框架 (web frameworks) 的一个重要组件。
  对于从浏览器发来的 HTTP 请求，URL 映射模块会解析请求中的 URL 地址，并将其分派给相应的处理代码。
  现在，请你来实现一个简单的 URL 映射功能。 
　　本题中 URL 映射功能的配置由若干条 URL 映射规则组成。当一个请求到达时，URL 映射功能会将请求中的
  URL 地址按照配置的先后顺序逐一与这些规则进行匹配。当遇到第一条完全匹配的规则时，匹配成功，
  得到匹配的规则以及匹配的参数。若不能匹配任何一条规则，则匹配失败。 
　　本题输入的 URL 地址是以斜杠 / 作为分隔符的路径，保证以斜杠开头。
  其他合法字符还包括大小写英文字母、阿拉伯数字、减号 -、下划线 _ 和小数点 .。
  例如，/person/123/ 是一个合法的 URL 地址，而 /person/123? 则不合法（存在不合法的字符问号 ?）。
  另外，英文字母区分大小写，因此 /case/ 和 /CAse/ 是不同的 URL 地址。 
　　对于 URL 映射规则，同样是以斜杠开始。除了可以是正常的 URL 地址外，还可以包含参数，有以下 3 种：
　　字符串 ：用于匹配一段字符串，注意字符串里不能包含斜杠。例如，abcde0123。 
　　整数 ：用于匹配一个不带符号的整数，全部由阿拉伯数字组成。例如，01234。 
　　路径 ：用于匹配一段字符串，字符串可以包含斜杠。例如，abcd/0123/。 
　　以上 3 种参数都必须匹配非空的字符串。简便起见，题目规定规则中 和 前面一定是斜杠，
  后面要么是斜杠，要么是规则的结束（也就是该参数是规则的最后一部分）。而 的前面一定是斜杠，
  后面一定是规则的结束。无论是 URL 地址还是规则，都不会出现连续的斜杠。 
输入格式 
　　输入第一行是两个正整数 n 和 m，分别表示 URL 映射的规则条数和待处理的 URL 地址个数，
  中间用一个空格字符分隔。 
　　第 2 行至第 n+1 行按匹配的先后顺序描述 URL 映射规则的配置信息。
  第 i+1 行包含两个字符串 pi 和 ri，其中 pi 表示 URL 匹配的规则，ri 表示这条 URL 匹配的名字。
  两个字符串都非空，且不包含空格字符，两者中间用一个空格字符分隔。 
　　第 n+2 行至第 n+m+1 行描述待处理的 URL 地址。第 n+1+i 行包含一个字符串 qi，
  表示待处理的 URL 地址，字符串中不包含空格字符。
样例输入
5 4
/articles/2003/ special_case_2003
/articles/<int>/ year_archive
/articles/<int>/<int>/ month_archive
/articles/<int>/<int>/<str>/ article_detail
/static/<path> static_serve
/articles/2004/
/articles/1985/09/aloha/
/articles/hello/
/static/js/jquery.js
样例输出
year_archive 2004
article_detail 1985 9 aloha
404
static_serve js/jquery.js
样例说明
　　对于第 1 个地址 /articles/2004/，无法匹配第 1 条规则，可以匹配第 2 条规则，参数为 2004。
　　对于第 2 个地址 /articles/1985/09/aloha/，只能匹配第 4 条规则，参数依次为 1985、9
  （已经去掉前导零）和 aloha。
　　对于第 3 个地址 /articles/hello/，无法匹配任何一条规则。
　　对于第 4 个地址 /static/js/jquery.js，可以匹配最后一条规则，参数为 js/jquery.js。
数据规模和约定
1 ≤ n ≤ 100，1 ≤ m ≤ 100。
　　所有输入行的长度不超过 100 个字符（不包含换行符）。
　　保证输入的规则都是合法的。
*/

#include <iostream>
#include <string>
#include <vector>
#include <string.h>
using namespace std;
typedef struct {
    vector<string> container;

}Rules;
bool IsLegal(string url)
{
    for (int i = 0; i < url.length(); i++)
    {
        if ((url[i] > '9') || (url[i] < '0'))
        {
            if ((url[i] > 'Z') || (url[i] < 'A'))
            {
                if ((url[i] > 'z') || (url[i] < 'a'))
                {
                    if ((url[i] != '-') && (url[i] != '_') && (url[i] != '.') && (url[i] != '/'))
                    {
                        return false;
                    }
                }
            }
        }
        
    }
    return true;
}
bool IsNumber(string url)
{
    for (int i = 0; i < url.length(); i++)
    {
        if ((url[i] < '0') || (url[i] > '9'))
        {
            return false;
        }
    }
    return true;
}
bool IsString(string url)
{
    for (int i = 0; i < url.length(); i++)
    {
        if ((url[i] == '/'))
        {
            return false;
        }
    }
    return true;
}
bool Match(Rules a[100], int n, string url, string& out,int& serial)
{
    if (!IsLegal(url))
    {
        return false;
    }
    int j = 1;
    string temp = "";
    int word = 0;
    for (int i = 0; i < n; i++)
    {
        out = "";
        word = 0;
        j = 1;
        for (int k = 0; k < a[i].container.size(); k++)
        {
            if (a[i].container[k] == "<int>")
            {
                int word1 = 0;
                while ((url[j] != '/') && (j < url.size()))
                {
                    if (word1 == 0)
                    {
                        if (url[j] == '0')
                        {
                            j++;
                        }
                        else
                        {
                            word1 = 1;
                        }
                    }
                    else
                    {
                        temp += url[j++];
                    }
                    
                }
                j++;
                if (!IsNumber(temp))
                {
                    temp = "";
                    break;
                }
                else
                {
                    out += temp;
                    out += " ";
                    word++;
                }
            }
            else if (a[i].container[k] == "<str>")
            {
                while ((url[j] != '/') && (j < url.size()))
                {
                    temp += url[j++];
                }
                j++;
                if (!IsString(temp))
                {
                    temp = "";
                    break;
                }
                else
                {
                    out += temp;
                    out += " ";
                    word++;
                    
                }

            }
            else if (a[i].container[k] == "<path>")
            {
                while (j < url.size())
                {
                    temp += url[j++];
                }
                out += temp;
                out += " ";
                serial = i;
                return true;
            }
            else
            {
                while ((url[j] != '/') && (j < url.size()))
                {
                    temp += url[j++];
                }
                j++;
                if (temp != a[i].container[k])
                {
                    temp = "";
                    break;
                }
                else
                {
                   // out += temp;
                   // out += " ";
                    word++;
                }
            }
            temp = "";
            if ((word == a[i].container.size()) && (j >= url.size()))
            {
                serial = i;
                
                return true;
            }
        }
    }
    return false;
}
int main()
{
    int n;
    int m;
    cin >> n;
    cin.ignore();
    cin >> m;
    cin.ignore();
    Rules a[100];
    vector<string> Name;
    char r[101];
    
    const char sign[2] = "/";
    char* token;
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> r;
        cin.ignore();
        token = strtok(r, sign);
        while (token != NULL)
        {
            a[i].container.push_back(token);
            token = strtok(NULL, sign);
        }
        cin >> r;
        cin.ignore();
        Name.push_back(r);
    }
    vector<string> ultimate;
    string url;
   
    int serial = -1;
    for (int i = 0; i < m; i++)
    {
        string out = "";
        cin >> url;
        cin.ignore();
        if (!Match(a, n, url, out, serial))
        {
            out = "404";
            ultimate.push_back(out);
        }
        else
        {
            string temp;
            temp = Name[serial] += " ";
            temp += out;
            ultimate.push_back(temp);
        }
        
    }
    for (int i = 0; i < ultimate.size(); i++)
    {
        if (ultimate[i] == "404")
        {
            cout << 404 << endl;
        }
        else
        {
            cout << ultimate[i] << endl;
        }
        
    }
    return 0;
}