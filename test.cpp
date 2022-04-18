#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using std::vector, std::string, std::pair;

/*
给定一个可包含重复数字的序列 nums ，按任意顺序 返回所有不重复的全排列。 
*/
class Solution
{
    // 传参 const string &s 比 const string 要快得多！！
    int dp(int &maxLen, int curNode, const vector<vector<int>> &children, const string &s)
    {
        int max = 0;
        int subMax = 0;
        for (const int child : children[curNode])
        {
            if (s[child] == s[curNode])
            {
                // Only DP
                dp(maxLen, child, children, s);
            }
            else
            {
                // DP and update
                const int childDp = dp(maxLen, child, children, s);
                if (childDp > max)
                {
                    subMax = max;
                    max = childDp;
                }
                else if (childDp > subMax)
                {
                    subMax = childDp;
                }
            }
        }
        int res = max + 1;
        maxLen = std::max(maxLen, max + subMax + 1);
        return res;
    }

    int dp(int &maxLen, int curNode, const std::unordered_map<int, vector<int>> &children)
    {
        int max = 0;
        int subMax = 0;
        for (const int child : children.at(curNode))
        {
            // DP and update
            const int childDp = dp(maxLen, child, children);
            if (childDp > max)
            {
                subMax = max;
                max = childDp;
            }
            else if (childDp > subMax)
            {
                subMax = childDp;
            }
        }
        int res = max + 1;
        maxLen = std::max(maxLen, max + subMax + 1);
        return res;
    }

public:
    int longestPath(vector<int> &parent, string s)
    {
        const int n = parent.size();
        vector<vector<int>> children(n);

        for (int i = 1; i < n; i++)
        {
            children[parent[i]].push_back(i);
        }

        int ans = 0;
        dp(ans, 0, children, s);
        return ans;
    }

    int treeDiameter(vector<vector<int>> &edges)
    {
        if (edges.empty()) {
            return 0;
        }
        std::unordered_map<int, vector<int>> children;
        for (const auto &edge : edges) {
            const int n1 = edge[0];
            const int n2 = edge[1];
            children[n1].push_back(n2);
            if (children.find(n2) == children.end()) {
                children[n2] = {};
            }
        }

        int ans = 0;
        dp(ans, 0, children);
        return ans - 1;
    }
};

int main()
{
}

/*
PB19061341
niuniu123456
*/