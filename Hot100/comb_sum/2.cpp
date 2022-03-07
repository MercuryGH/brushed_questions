#include <vector>
using std::vector;

class Solution
{
    vector<bool> vis;

    void dfs(vector<vector<int>> &combinations, vector<int> &curCombination, const vector<int> &candidates, const int target)
    {
    }

public:
    vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
    {
        const int n = candidates.size();
        vis.resize(n, false);

        vector<vector<int>> ans;
        vector<int> curCombination;
        dfs(ans, curCombination, candidates, target);
        return ans;
    }
};