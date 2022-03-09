#include <vector>
#include <algorithm>
using std::vector;

/**
 * 本题重点是去重，比较具有技巧性
 * 
 * 与 1.cpp 其实差距不大
 */
class Solution
{
    vector<bool> vis;
    int n;

    void dfs(vector<vector<int>> &combinations, vector<int> &curCombination, const vector<int> &candidates, const int target, const int index)
    {
        if (target == 0)
        {
            combinations.push_back(curCombination);
            return;
        }
        if (target < 0)
        {
            return;
        }

        for (int i = index; i < n; i++)
        {
            if (i != 0 && candidates[i - 1] == candidates[i] && vis[i - 1] == false)
            // 去重必备语句：如果之前的没选，那么这个也不能选
            {
                continue;
            }
            if (vis[i] == false)
            {
                vis[i] = true;
                curCombination.push_back(candidates[i]);
                dfs(combinations, curCombination, candidates, target - candidates[index], i + 1);
                curCombination.pop_back();
                vis[i] = false;
            }
        }
    }

public:
    vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
    {
        std::sort(candidates.begin(), candidates.end()); // 去重必须
        vis.resize(n, false);

        vector<vector<int>> ans;
        vector<int> curCombination;
        dfs(ans, curCombination, candidates, target, 0);
        return ans;
    }
};