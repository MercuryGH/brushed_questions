#include <cstdio>
#include <iostream>
#include <string>
#include <map>
#include <cctype>
using namespace std;

void reverse(string &s)
{
    for (int i = 0; i < s.size() / 2; ++i)
    {
        char c = s[i];
        s[i] = s[s.size() - i - 1];
        s[s.size() - i - 1] = c;
    }
}

int main()
{
    string s;
    cin >> s;
    string now;

    for (int i = 0; i < s.size(); ++i) //去除括号
    {
        if (isdigit(s[i]) || isalpha(s[i]) || s[i] == '(' || s[i] == '[') //右括号之外的字符直接入栈
            now.push_back(s[i]);
        else
        {
            string tmp;
            while (now.back() != '(' && now.back() != '[') //记录当前这一对括号之间的字符串
            {
                tmp.push_back(now.back());
                now.pop_back();
            }
            now.pop_back(); //左括号出栈
            reverse(tmp);

            i++;
            int num = 0;
            while (i < s.size() && isdigit(s[i])) //计算后面的系数
            {
                num = num * 10 + (s[i] - '0');
                i++;
            }
            if (num == 0) //防止括号后面没有系数的情况
                num = 1;
            i--;
            while (num > 0)
            {
                now += tmp;
                num--;
            }
        }
    }
    map<string, int> m;
    string t;
    for (int i = 0; i < now.size(); ++i) //计算各个元素数量
    {
        if (now[i] >= 'a' && now[i] <= 'z') //如果是小写字母
        {
            t.push_back(now[i]);
        }
        else if (now[i] >= 'A' && now[i] <= 'Z') //如果是大写字母
        {
            if (!t.empty())
            {
                m[t]++;
                t.clear();
                t.push_back(now[i]);
            }
            else
                t.push_back(now[i]);
        }
        else //如果是数字
        {
            m[t] += now[i] - '0';
            t.clear();
        }
    }
    if (!t.empty()) //不要漏掉最后一个元素
        m[t]++;
    map<string, int>::iterator it = m.begin();
    while (it != m.end())
    {
        cout << it->first << it->second;
        it++;
    }
    cout << endl;
    return 0;
}
