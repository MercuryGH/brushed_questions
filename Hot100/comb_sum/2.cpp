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
    int n;
    void dfs(vector<vector<int>> &combinations, vector<int> &curCombination, vector<bool> &vis, const int index, const int curSum, const vector<int> &candidates, const int target) {
        if (curSum == target) {
            combinations.push_back(curCombination);
            return;
        }
        if (curSum > target) {
            return;
        }

        for (int i = index; i < n; i++) {
            if (i > 0 && candidates[i] == candidates[i - 1] && vis[i - 1] == false) {
                continue;
            }

            vis[i] = true;
            curCombination.push_back(candidates[i]);
            dfs(combinations, curCombination, vis, i + 1, curSum + candidates[i], candidates, target);
            curCombination.pop_back();
            vis[i] = false;
        }
    }
public:
    vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
    {
        std::sort(candidates.begin(), candidates.end());
        n = candidates.size();
        vector<vector<int>> ans;
        vector<bool> vis(n, false);
        vector<int> curCombination;
        dfs(ans, curCombination, vis, 0, 0, candidates, target);
        return ans;
    }
};