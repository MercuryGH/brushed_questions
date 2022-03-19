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
#include <unordered_map>
#include <unordered_set>
#include <vector>
using std::vector, std::string;

/**
 * 删除无效的括号，要求返回所有删除的括号最少的方案，DFS/BFS进阶题目
 * BFS（层序遍历）比DFS简单得多，且时间复杂度并无劣势（虽然没办法搞一些奇奇怪怪的剪枝），因此推荐BFS
 *
 * 思路：
 * 1. 枚举原始字符串的每个括号，暴力删掉，结果存在一个集合里（自然去重）
 * 2. 在下一层，删除的括号个数就是1，枚举所有方案，如果括号匹配，就加入答案集合。
 *    如果答案集合不为空，直接返回即可；否则继续暴力删，BFS。
 */
class Solution
{
    // s 中是否含有相等数目的左括号和右括号
    bool isBalance(const string s)
    {
        const int n = s.length();
        int cnt = 0;
        for (int i = 0; i < n; i++)
        {
            if (s[i] == '(')
            {
                cnt++;
            }
            if (s[i] == ')')
            {
                cnt--;
                if (cnt < 0)
                {
                    return false;
                }
            }
        }
        return cnt == 0;
    }

public:
    vector<string> removeInvalidParentheses(string s)
    {
        std::unordered_set<string> curLevel;
        curLevel.insert(s);
        while (curLevel.empty() == false)
        {
            std::unordered_set<string> ans;
            for (const string &s : curLevel)
            {
                if (isBalance(s))
                {
                    ans.insert(s);
                }
            }
            if (ans.empty() == false) // 删出答案了，赶紧返回
            {
                return vector<string>(ans.begin(), ans.end());
            }

            std::unordered_set<string> nextLevel;
            for (const string &s : curLevel)
            {
                for (int i = 0; i < s.length(); i++)
                {
                    if (s[i] == '(' || s[i] == ')') // 是个括号就暴力删，等到下一层再验证
                    {
                        nextLevel.insert(s.substr(0, i) + s.substr(i + 1));
                    }
                }
            }
            curLevel = nextLevel;
        }

        return {};
    }
};

int main()
{
}