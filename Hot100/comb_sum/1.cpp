#include <vector>

/**
 * 组合总和
 * 策略：选或不选。不必记录vis数组。
 * candidates 中的 同一个 数字可以 无限制重复被选取 。如果至少一个数字的被选数量不同，则两种组合是不同的。
 *
 * 典型DFS，建议背题
 */
class Solution
{
    int n;

    void dfs(std::vector<std::vector<int>> &combinations, std::vector<int> &curCombination, const std::vector<int> &candidates, int target, int index)
    {
        if (target == 0)
        {
            combinations.push_back(curCombination);
            return;
        }
        if (target < 0)
        { // 剪枝，可以删
            return;
        }

        for (int i = index; i < n; i++)
        {
            curCombination.push_back(candidates[i]);
            dfs(combinations, curCombination, candidates, target - candidates[i], i);
            curCombination.pop_back();
        }
    }

public:
    std::vector<std::vector<int>> combinationSum(std::vector<int> &candidates, int target)
    {
        n = candidates.size();

        std::vector<std::vector<int>> ans;
        std::vector<int> combination;
        dfs(ans, combination, candidates, target, 0);
        return ans;
    }
};