#include <algorithm>
#include <ctime>
#include <cmath>
#include <iostream>
#include <list>
#include <memory>
#include <queue>
#include <stack>
#include <set>
#include <sstream>
#include <string>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using std::vector, std::string;

bool isLower(char c)
{
    return c >= 'a' && c <= 'z';
}

bool isUpper(char c)
{
    return c >= 'A' && c <= 'Z';
}

class Solution
{
    bool isLeftBracket(char c)
    {
        return c == '[' || c == '(';
    }
    bool isRightBracket(char c)
    {
        return c == ']' || c == ')';
    }

public:
    string getString(const string s, int &sIndex)
    {
        const int len = s.size();

        string res;
        int repeatCnt = 0; // 读到的重复数，如 3[aa] 中的 3
        for (int i = sIndex; i < len; i++)
        {
            const char curChar = s[i];

            if (isdigit(curChar))
            { // 十进制解析重复数
                repeatCnt *= 10;
                repeatCnt += curChar - '0';
            }
            else if (isRightBracket(curChar))
            {        // 开始递归
                i++; // 进入待解析的部分
                string parsedStr = getString(s, i);
                if (repeatCnt == 0)
                    repeatCnt = 1;
                while (repeatCnt--)
                { // 让 res += (parsedStr * repeatCnt)
                    res += parsedStr;
                }
                repeatCnt = 0;
            }
            else if (isLeftBracket(curChar))
            {
                sIndex = i; // 更新全局字符串 s 的下标（可以看作是 getString() 的第二个返回值）
                return res;
            }
            else
            {
                if (repeatCnt != 0)
                {
                    string getStr;
                    if (isUpper(s[i]))
                    {
                        getStr = s.substr(i, 1);
                    }
                    else
                    {
                        getStr = s.substr(i, 2);
                        i++;
                    }
                    while (repeatCnt--)
                    {
                        res += getStr;
                    }
                    // std::cout << getStr << "\n";

                    repeatCnt = 0;
                }
                else
                {
                    res += curChar;
                }
            }
        }
        return res;
    }
};

int main()
{
    freopen("testdata.in", "r", stdin);
    string st;
    std::cin >> st;

    std::reverse(st.begin(), st.end());

    Solution s;
    int sIndex = 0;
    string ans = s.getString(st, sIndex);

    std::map<string, int> elementFreq;
    for (int i = 0; i < ans.size(); i++)
    {
        if (isUpper(ans[i]))
        {
            elementFreq[ans.substr(i, 1)]++;
        }
        else // lower, find next Upper
        {
            string s = ans.substr(i, 2);
            std::reverse(s.begin(), s.end());
            elementFreq[s]++;
            i++;
        }
    }

    ans = "";
    for (const auto [k, v] : elementFreq)
    {
        ans += k;
        ans += std::to_string(v);
    }
    std::cout << ans << "\n";

    return 0;
}