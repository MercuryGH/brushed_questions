#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <list>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using std::vector, std::string;

class Solution
{
    int n;

    bool outOfBound(int x, int y)
    {
        return x < 0 || x >= n || y < 0 || y >= n;
    }
    bool canBeAttacked(const vector<int> &curYs, int x, int y)
    {
        // 列
        for (const int curY : curYs)
        {
            if (curY == y)
            {
                return true;
            }
        }
        // 正对角线
        int token = y - x;
        for (int i = 0; i < x; i++)
        {
            int j = token + i;
            if (outOfBound(i, j))
            {
                continue;
            }

            if (curYs[i] == j)
            {
                return true;
            }
        }
        // 斜对角线
        token = y + x;
        for (int i = 0; i < x; i++)
        {
            int j = token - i;
            if (outOfBound(i, j))
            {
                continue;
            }

            if (curYs[i] == j)
            {
                return true;
            }
        }

        return false;
    }

    /**
     * curYs[i] = j，表示 (i, j) 处被放置了一枚棋子
     */
    void dfs(vector<vector<string>> &ans, vector<int> &curYs, int step)
    {
        if (step == n)
        {
            vector<string> grid(n);
            string emptyLine;
            for (int i = 0; i < n; i++)
            {
                emptyLine += '.';
            }
            for (int i = 0; i < n; i++)
            {
                grid[i] = emptyLine;
            }

            for (int i = 0; i < n; i++)
            {
                grid[i][curYs[i]] = 'Q';
            }
            ans.push_back(grid);
            return;
        }

        for (int i = 0; i < n; i++)
        {
            if (canBeAttacked(curYs, step, i) == false)
            {
                curYs.push_back(i);
                dfs(ans, curYs, step + 1);
                curYs.pop_back();
            }
        }
    }

public:
    vector<vector<string>> solveNQueens(int n)
    {
        this->n = n;

        vector<vector<string>> ans;
        vector<int> curYs;
        dfs(ans, curYs, 0);
        return ans;
    }
};