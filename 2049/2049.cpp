#include <vector>
using std::vector;

class Solution
{
public:
    long long maxScore = 0;
    int cnt = 0;
    int n;
    vector<vector<int>> children;

    /**
     * 返回以 node 为根结点的子树的大小，同时更新答案
     */
    int dfs(int node)
    {
        long long score = 1;
        int highLevelTreeSize = n - 1; // 一开始已经被删了一个
        for (const int child : children[node])
        {
            int t = dfs(child);
            score *= t;
            highLevelTreeSize -= t; // 技巧：同时更新高层树的大小
        }

        if (node != 0)
        {
            score *= highLevelTreeSize;
        }

        if (score == maxScore)
        {
            cnt++;
        }
        else if (score > maxScore)
        {
            maxScore = score;
            cnt = 1;
        }

        return n - highLevelTreeSize;
    }

    int countHighestScoreNodes(vector<int> &parents)
    {
        n = parents.size();
        children = vector<vector<int>>(n);
        for (int i = 0; i < n; i++)
        {
            int p = parents[i];
            if (p != -1)
            {
                children[p].push_back(i);
            }
        }
        dfs(0);
        return cnt;
    }
};